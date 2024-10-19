#include "PlayerBulletNavigationComponent.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

PlayerBulletNavigationComponent::PlayerBulletNavigationComponent()
{

}

PlayerBulletNavigationComponent::PlayerBulletNavigationComponent(Json::Value componentJSON)
	: NavigationComponent(componentJSON)
{

	int todd = 1;

}

PlayerBulletNavigationComponent::~PlayerBulletNavigationComponent()
{

}

void PlayerBulletNavigationComponent::reset()
{
	m_closestDistance.reset();
}

void PlayerBulletNavigationComponent::update()
{

	//This bullet may be marked for removal but not removed yet.
	if (parent()->removeFromWorld() == true) {
		//return;
	}

	NavigationComponent::update();

	auto targetDestination = getDestination();


	//Calculate the leading edge position of the bullet
	float angleRadians = parent()->getAngle();
	float angleDegrees = parent()->getAngleInDegrees();
	SDL_FPoint bulletCenterPosition = parent()->getCenterPosition();
	float halfLength = parent()->getSize().x;
	float halfWidth = parent()->getSize().y;

	SDL_FPoint leadingEdgePosition{};

	leadingEdgePosition.x = bulletCenterPosition.x + parent()->getSize().x * cos(angleRadians);
	leadingEdgePosition.y = bulletCenterPosition.y + parent()->getSize().y * sin(angleRadians);

	//Distance between our master oobject and the destination
	float targetDistance = util::calculateDistance(leadingEdgePosition, targetDestination);

	//if this distance is > the closest distance that the bullet has gotten to the target destination
	//then it means that it's gotten as close to the destination as it's going to
	if (m_closestDistance.has_value() && m_closestDistance.value() < targetDistance) {

		std::optional<std::shared_ptr<GameObject>> explosionObject =
			parent()->parentScene()->objectPoolManager().getPooledObject("EXPLOSION1_POOL");
		if (explosionObject.has_value()) {
			explosionObject.value()->setPosition(targetDestination.x, targetDestination.y);

			parent()->parentScene()->addGameObject(explosionObject.value(), GameLayer::MAIN);
		}


		//auto explosionObject = SceneManager::instance().addGameObject("PARTICLE_EXPLOSION_1", GameLayer::MAIN, -1, -1);
		//explosionObject->setPosition(targetDestination.x, targetDestination.y);
		
		//std::cout << "Bullet explode" << std::endl;

		parent()->reset();
		parent()->setRemoveFromWorld(true);
		m_closestDistance.reset();

	}
	else {

		m_closestDistance = targetDistance;

	}
	//ImGui::Value("Bullet Distance", targetDistance);



}
