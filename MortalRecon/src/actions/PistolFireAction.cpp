#include "PistolFireAction.h"

void PistolFireAction::perform(GameObject* gameObject)
{

	const auto& weaponComponent = gameObject->getComponent<WeaponComponent>(ComponentTypes::WEAPON_COMPONENT);
	b2Vec2 position = {0,0};
	float angle = 0;

	std::string bulletPoolId = weaponComponent->getBulletPoolId();

	//Sound
	const auto& soundComponent = gameObject->getComponent<SoundComponent>(ComponentTypes::SOUND_COMPONENT);
	soundComponent->playSound("FIRE_SOUND");

	//If this object is NOT a physics object then we need to divide by the scale factor to convert the X.Y
	if (gameObject->hasComponent(ComponentTypes::PHYSICS_COMPONENT)) {
		const auto& physicsComponent = gameObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
		position = physicsComponent->position();
		angle = physicsComponent->angle();
	}
	else {
		const auto& transformComponent = gameObject->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
		position = transformComponent->position();
		position.x /= GameConfig::instance().scaleFactor();
		position.y /= GameConfig::instance().scaleFactor();
		angle = util::degreesToRadians(transformComponent->angle());
	}
	
	weaponComponent->fire(position, angle);

}
