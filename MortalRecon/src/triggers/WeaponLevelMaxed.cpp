#include "WeaponLevelMaxed.h"
#include "../MRContextManager.h"

#include "../GameConstants.h"

extern std::unique_ptr<Game> game;


WeaponLevelMaxed::WeaponLevelMaxed():
	Trigger()
{
	m_triggerOnlyOnce = true;
	m_triggerName = "WeaponLevelMaxed";

}

bool WeaponLevelMaxed::hasMetCriteria(Scene* scene)
{

	bool hasMet{ false };

	if (m_triggerOnlyOnce == false || ( m_triggerOnlyOnce && m_hasTriggered == false)) {


		auto& weaponLevel = game->contextMananger()->getStatusItem(StatusItemId::PLAYER_WEAPON_LEVEL);
		if (weaponLevel.isAtMax()) {

			hasMet = true;
		}

	}

	return hasMet;
}


void WeaponLevelMaxed::execute()
{

	auto& scene = SceneManager::instance().currentScene();
	auto pieces = scene.getGameObjectsByType("SCRAP_PIECE");

	m_hasTriggered = true;

	//Remove all scrap from the level
	for (auto& piece : pieces) {

		piece->setRemoveFromWorld(true);

	}

}
