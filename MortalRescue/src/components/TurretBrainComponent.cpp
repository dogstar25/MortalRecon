#include "TurretBrainComponent.h"

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdlrenderer.h"



TurretBrainComponent::TurretBrainComponent(Json::Value definitionJSON)
	: BrainComponent(definitionJSON)
{

	m_currentState = BrainState::IDLE;

	m_fireDelayTimer = Timer(.2);

}

//void TurretBrainComponent::postInit()
//{
//	//Call base brain postinit
//	BrainComponent::postInit();
//
//	//Get all WayPoints
//	for (const auto& gameObject : parent()->parentScene()->gameObjects()[LAYER_ABSTRACT]) {
//
//		if (gameObject->hasTrait(TraitTag::navigation)) {
//
//			const auto& navComponent = gameObject->getComponent<NavigationComponent>(ComponentTypes::NAVIGATION_COMPONENT);
//			if (navComponent->type() == NavigationObjectType::WAYPOINT) {
//				m_wayPoints.push_back(gameObject.get());
//			}
//
//		}
//	}
//
//	//Do an random sort of the waypoints order
//	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
//	std::shuffle(m_wayPoints.begin(), m_wayPoints.end(), std::default_random_engine(seed));
//
//}

void TurretBrainComponent::update()
{

	BrainComponent::update();

	//Determine state
	m_currentState = _determineState();

	switch (m_currentState) {

	case BrainState::ENGAGE:
		_doEngage();
		break;
	case BrainState::DEPLOY:
		_doDeploy();
		break;
	case BrainState::UNDEPLOY:
		_doUnDeploy();
		break;
	default:
		_doIdle();
		break;
	}

}

int TurretBrainComponent::_determineState()
{

	int state{ m_currentState };

	//Can we see the enemy/player?
	std::optional<SDL_FPoint> playerLocation = _detectPlayer();
	if (playerLocation.has_value()) {

		if (m_currentState == BrainState::IDLE) {
			state = BrainState::DEPLOY;
		}
		else if (m_currentState == BrainState::DEPLOY) {
			
			const auto& animationComponent = parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
			//If animation state is ANIMATION_ACTIVE then it has finished the deploy animation
			if (animationComponent->currentAnimationState() == ANIMATION_ACTIVE) {
				state = BrainState::ENGAGE;
			}
		}
		else if (m_currentState == BrainState::UNDEPLOY) {

			const auto& animationComponent = parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
			state = BrainState::DEPLOY;

		}
		else if (m_currentState == BrainState::ENGAGE) {

			//stay engage?

		}

	}
	else {
		if (m_currentState == BrainState::DEPLOY || m_currentState == BrainState::ENGAGE) {
			state = BrainState::UNDEPLOY;
		}
		else if (m_currentState == BrainState::UNDEPLOY) {

			//If the undeploy animation is done, then set the brain to IDLE
			const auto& animationComponent = parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
			if (animationComponent->currentAnimationState() == ANIMATION_IDLE) {
				state = BrainState::IDLE;
			}


		}
	}

	return state;

}

void TurretBrainComponent::_doDeploy()
{

	const auto& animationComponent = parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);

	animationComponent->animate(ANIMATION_DEPLOY, ANIMATE_ONE_TIME);
	animationComponent->setDefaultAnimationState(ANIMATION_ACTIVE);

}

void TurretBrainComponent::_doUnDeploy()
{
	const auto& physicsComponent = parent()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& transformComponent = parent()->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
	const auto& animationComponent = parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);

	float angleRadians = util::degreesToRadians(transformComponent->originalAngle());
	physicsComponent->setAngle(angleRadians);
	physicsComponent->update();

	animationComponent->animate(ANIMATION_UNDEPLOY, ANIMATE_ONE_TIME);
	animationComponent->setDefaultAnimationState(ANIMATION_IDLE);

}

void TurretBrainComponent::_doIdle()
{
	const auto& animationComponent = parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
	animationComponent->setCurrentAnimationState(ANIMATION_IDLE);

}

void TurretBrainComponent::_doEngage()
{
	bool enemyTargeted{ false };

	std::optional<SDL_FPoint> playerLocation = _detectPlayer();
	if (playerLocation.has_value()) {

		b2Vec2 targetLoc = { playerLocation.value().x, playerLocation.value().y };
		enemyTargeted = _rotateTowards(targetLoc);

	}

	if (m_fireDelayTimer.hasMetTargetDuration() && enemyTargeted == true) {

		auto action = parent()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
		action->performUsageAction();

	}

	

}

bool TurretBrainComponent::_rotateTowards(b2Vec2 targetPoint)
{
	bool onTarget{false};

	auto physicsComponent = parent()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	auto transformComponent = parent()->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
	auto currentAngle = physicsComponent->angle();
	auto rotationCenter = transformComponent->getCenterPosition();

	//calculate the angle
	auto desiredAngle = atan2f(
		(targetPoint.y - rotationCenter.y),
		(targetPoint.x - rotationCenter.x));
	desiredAngle = util::normalizeRadians(desiredAngle);

	auto desiredAngleDegrees = util::radiansToDegrees(desiredAngle);
	auto objectAngleDegrees = util::radiansToDegrees(currentAngle);

	float rotationVelocity{ 0 };

	//Get the objects action and vitality components
	auto action = parent()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
	auto vitality = parent()->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

	if ((desiredAngle - currentAngle) < 0.0) {
		rotationVelocity = vitality->rotateSpeed() * -1;
	}
	else {
		rotationVelocity = vitality->rotateSpeed();
	}

	auto difference = abs(desiredAngle - currentAngle);

	//Once the angle is very close then set the angle directly
	if (difference < 0.19) {
		action->performRotateAction(0);
		onTarget = true;

		//This next code makes the aim dead on balls accurate - may be too hard
		const auto& physicsComponent = parent()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
		physicsComponent->setAngle(desiredAngle);
		physicsComponent->update();

	}
	else {

		action->performRotateAction(rotationVelocity);
	}

	return onTarget;
}

std::optional<SDL_FPoint> TurretBrainComponent::_detectPlayer()
{

	std::optional<SDL_FPoint> playerPosition{};

	for (auto& seenObject : m_seenObjects) {

		if (seenObject.gameObject->hasTrait(TraitTag::player)) {

			playerPosition = seenObject.gameObject->getCenterPosition();
			break;
		}
	}

	return playerPosition;

}