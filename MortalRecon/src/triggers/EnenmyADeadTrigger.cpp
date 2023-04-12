#include "EnemyADeadTrigger.h"
#include "../GameConstants.h"


extern std::unique_ptr<Game> game;

EnemyADeadTrigger::EnemyADeadTrigger() :
	Trigger()
{
	m_triggerOnlyOnce = true;
	m_triggerName = "EnenmyADeadTrigger";

}

bool EnemyADeadTrigger::hasMetCriteria(Scene* scene)
{

	bool hasMet{ false };

	if (m_triggerOnlyOnce == false || (m_triggerOnlyOnce && m_hasTriggered == false)) {

		const auto& enemyAList = scene->getGameObjectsByName("EnemyA");
		if (enemyAList.empty()) {
			hasMet = true;
		}

	}

	return hasMet;
}

void EnemyADeadTrigger::execute()
{


}

