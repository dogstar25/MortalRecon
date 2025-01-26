#include "ScoreManager.h"
#include <utility>



ScoreManager::ScoreManager()
{

	m_maxTimeToMax = 600;
	m_maxScore = 2000;
}


ScoreManager& ScoreManager::instance()
{

	static ScoreManager singletonInstance;
	return singletonInstance;

}

void ScoreManager::init()
{
	resetForNewLevel();
	m_score = m_maxScore;
}


void ScoreManager::update(int playerDeaths, float timeToMax)
{

	float maxPossibleScore = m_maxScore - (playerDeaths * 200);
	float speedBonus = m_maxTimeToMax / m_timeToMax;
	float score = std::min(maxPossibleScore, 2000 - (playerDeaths * 200) + speedBonus);

	m_score = score;

}

void ScoreManager::resetForNewLevel()
{

	m_timeToMax = m_maxTimeToMax;

}
