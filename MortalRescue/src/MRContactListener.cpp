#include "MRContactListener.h"
#include "SceneManager.h"

#include <iostream>

#include "MRContextManager.h"
#include "game.h"
#include "GameConstants.h"
#include "SoundManager.h"
#include "particleEffects/GameParticleEffects.h"
#include "components/InventoryComponent.h"
#include "components/PistolWeaponComponent.h"

extern std::unique_ptr<Game> game;


void MRContactListener::_bullet_wall(GameObject* bullet, GameObject* wall, b2Vec2 contactPoint)
{

	//Build a One-Time particle emitter object
	auto particleEmitterObject = SceneManager::instance().addGameObject("PARTICLE_X_EMITTER", LAYER_MAIN, -1, -1);
	const auto& particleComponent = particleEmitterObject->getComponent<ParticleComponent>(ComponentTypes::PARTICLE_X_COMPONENT);
	particleComponent->addParticleEffect(ParticleEffects::ricochet);

	//Convert from box2d to gameWorld coordinates
	contactPoint.x *= GameConfig::instance().scaleFactor();
	contactPoint.y *= GameConfig::instance().scaleFactor();
	particleEmitterObject->setPosition(contactPoint.x, contactPoint.y);

	//Set flag for removal for the Bullet
	bullet->setRemoveFromWorld(true);

}

void MRContactListener::_playerBullet_droneShield(GameObject* playerBullet, GameObject* droneShield, b2Vec2 contactPoint)
{

	auto particleEmitterObject = SceneManager::instance().addGameObject("PARTICLE_X_EMITTER", LAYER_MAIN, -1, -1);
	auto particleComponent = particleEmitterObject->getComponent<ParticleXComponent>(ComponentTypes::PARTICLE_X_COMPONENT);
	//auto particleEmitterObject = SceneManager::instance().addGameObject("PARTICLE_EMITTER", LAYER_MAIN, -1, -1);
	//auto particleComponent = particleEmitterObject->getComponent<ParticleComponent>(ComponentTypes::PARTICLE_COMPONENT);

	particleComponent->setType(ParticleEmitterType::ONETIME);
	//particleComponent->setType(ParticleEmitterType::CONTINUOUS);

	//Convert from box2d to gameWorld coordinates
	contactPoint.x *= GameConfig::instance().scaleFactor();
	contactPoint.y *= GameConfig::instance().scaleFactor();
	particleEmitterObject->setPosition(contactPoint.x, contactPoint.y);

	//Set flag for removal for the Bullet
	playerBullet->setRemoveFromWorld(true);

	//Test if the bullet is strong enought to destroy the shield piece
	auto bulletVitality = playerBullet->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);
	auto shieldVitality = droneShield->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);
	auto shieldHolds = shieldVitality->testResistance(bulletVitality->attackPower());
	if (shieldHolds == false) {

		particleComponent->addParticleEffect(ParticleEffects::impactSmoke);
		particleComponent->addParticleEffect(ParticleEffects::scrap);
		SoundManager::instance().playSound("SFX_IMPACT_1");

	}
	else {

		particleComponent->addParticleEffect(ParticleEffects::deflect);
		SoundManager::instance().playSound("SFX_IMPACT_3");
	}

}

void MRContactListener::_player_shieldScrap(GameObject* player, GameObject* shieldScrap, b2Vec2 contactPoint)
{

	//Acknowledge the scrap collection
	auto inventoryComponent = player->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
	auto scrapCount = inventoryComponent->addCollectible(CollectibleTypes::DRONE_SCRAP, 1);

	//Update the status Manager
	//static_cast<MRStatusManager*>(game->statusMananger())->hudValueMap()["HUD_SCRAP_VALUE"].adjust(1);
	game->contextMananger()->adjustValue("SCRAP_COUNT", 1);

	//Check to see if this upgrades the players weapon
	auto pistol = inventoryComponent->getItem(TraitTag::weapon);
	if (pistol.has_value()) {
		auto pistolWeaponComponent = pistol.value()->getComponent<PistolWeaponComponent>(ComponentTypes::WEAPON_COMPONENT);
		pistolWeaponComponent->checkLevelUp(scrapCount);
	}
	
	//flag the scrap item to be removed from the game and play a sound effect
	shieldScrap->setRemoveFromWorld(true);
	SoundManager::instance().playSound("SFX_PICKUP_2");

}

void MRContactListener::_enemyBullet_player(GameObject* bullet, GameObject* player, b2Vec2 contactPoint)
{

	//Update the status Manager
	game->contextMananger()->adjustValue("LIVES_COUNT", -1);

	//flag the scrap item to be removed from the game and play a sound effect
	bullet->setRemoveFromWorld(true);
	SoundManager::instance().playSound("SFX_PICKUP_2");

}
void MRContactListener::BeginContact(b2Contact* contact) {

	b2WorldManifold worldManifold;

	contact->GetWorldManifold(&worldManifold);
	b2Vec2 contactPoint = worldManifold.points[0];

	handleContact(contact, contactPoint);

}


void MRContactListener::EndContact(b2Contact* contact)
{


}



void MRContactListener::handleContact(b2Contact* contact, b2Vec2 contactPoint)
{

	//Get fixtures
	b2Fixture* fixture1 = contact->GetFixtureA();
	b2Fixture* fixture2 = contact->GetFixtureB();

	//Get the GameObjects attched to these fixtures
	GameObject* contact1 = reinterpret_cast<GameObject*>(fixture1->GetBody()->GetUserData().pointer);
	GameObject* contact2 = reinterpret_cast<GameObject*>(fixture2->GetBody()->GetUserData().pointer);

	//Get each fixtures' contactTag
	int contactTag1 = static_cast<int>(fixture1->GetUserData().pointer);
	int contactTag2 = static_cast<int>(fixture2->GetUserData().pointer);

	////////////////////////////////////
	// Player Bullet -  Wall Contact
	//////////////////////////////////
	if ((contactTag1 == ContactTag::PLAYER_BULLET && contactTag2 == ContactTag::WALL) ||
		(contactTag2 == ContactTag::PLAYER_BULLET && contactTag1 == ContactTag::WALL)) {

		if (contactTag1 == ContactTag::PLAYER_BULLET) {
			_bullet_wall(contact1, contact2, contactPoint);
		}
		else {
			_bullet_wall(contact2, contact1, contactPoint);
		}
	}

	////////////////////////////////////
	// Enemy Bullet -  Wall Contact
	//////////////////////////////////
	if ((contactTag1 == ContactTag::ENEMY_BULLET && contactTag2 == ContactTag::WALL) ||
		(contactTag2 == ContactTag::ENEMY_BULLET && contactTag1 == ContactTag::WALL)) {

		if (contactTag1 == ContactTag::ENEMY_BULLET) {
			_bullet_wall(contact1, contact2, contactPoint);
		}
		else {
			_bullet_wall(contact2, contact1, contactPoint);
		}

	}

	///////////////////////////////////
	// Player Bullet -  Drone Shield
	///////////////////////////////////
	if ((contactTag1 == ContactTag::PLAYER_BULLET && contactTag2 == ContactTag::DRONE_SHIELD) ||
		(contactTag2 == ContactTag::PLAYER_BULLET && contactTag1 == ContactTag::DRONE_SHIELD)) {

		if (contactTag1 == ContactTag::PLAYER_BULLET) {
			_playerBullet_droneShield(contact1, contact2, contactPoint);
		}
		else {
			_playerBullet_droneShield(contact2, contact1, contactPoint);
		}

	}

	///////////////////////////////////
	// Player - Drone Scrap
	///////////////////////////////////
	if ((contactTag1 == ContactTag::PLAYER_COLLISION && contactTag2 == ContactTag::SHIELD_SCRAP) ||
		(contactTag2 == ContactTag::PLAYER_COLLISION && contactTag1 == ContactTag::SHIELD_SCRAP)) {

		if (contactTag1 == ContactTag::PLAYER_COLLISION) {
			_player_shieldScrap(contact1, contact2, contactPoint);
		}
		else {
			_player_shieldScrap(contact2, contact1, contactPoint);
		}

	}

	///////////////////////////////////
	// Enemy Bullet - Player
	///////////////////////////////////
	if ((contactTag1 == ContactTag::PLAYER_HITBOX && contactTag2 == ContactTag::ENEMY_BULLET) ||
		(contactTag2 == ContactTag::PLAYER_HITBOX && contactTag1 == ContactTag::ENEMY_BULLET)) {

		if (contactTag1 == ContactTag::ENEMY_BULLET) {
			_enemyBullet_player(contact1, contact2, contactPoint);
		}
		else {
			_enemyBullet_player(contact2, contact1, contactPoint);
		}

	}

}






