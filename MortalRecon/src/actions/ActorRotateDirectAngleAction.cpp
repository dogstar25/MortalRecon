#include "ActorRotateDirectAngleAction.h"
#include "../components/GinaPlayerControlComponent.h"

void ActorRotateDirectAngleAction::perform(GameObject* gameObject, float angularVelocity)
{
	const auto& physicsComponent = gameObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& animationComponent = gameObject->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
	const auto& playerControlComponent = gameObject->getComponent<GinaPlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT);
	int mouseX = 0, mouseY = 0;
	int relMouseX = 0, relMouseY = 0;
	const int ANGLE_TOLERANCE = 2;
	const int ROTATE_SPEED = 20000;

	if (animationComponent && playerControlComponent->state().test(PlayerState::boosting) == false)
	{
		const uint32_t currentMouseStates = SDL_GetRelativeMouseState(&relMouseX, &relMouseY);
		if (relMouseX > 0 || relMouseY > 0) {
			animationComponent->animate(ANIMATION_RUN, ANIMATE_ONE_TIME);
		}
	}

	auto worldMousePosition = util::getMouseWorldPosition();

	float hostAngleDegrees = util::radiansToDegrees(physicsComponent->angle());
	float orientationAngle = atan2(gameObject->getCenterPosition().y - worldMousePosition.y, gameObject->getCenterPosition().x - worldMousePosition.x);
	float orientationAngleDegrees = util::radiansToDegrees(orientationAngle);

	orientationAngleDegrees += 180;

	gameObject->setAngleInDegrees(orientationAngleDegrees);

	//We need this little hack adjustment to ensure attachments to gina adjust to her new anlge that was set abruptly
	physicsComponent->applyImpulse(.1, { 0, 0 });

}
