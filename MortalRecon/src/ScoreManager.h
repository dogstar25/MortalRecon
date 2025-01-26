#pragma once
class ScoreManager
{

public:
	ScoreManager();
	
	static ScoreManager& instance();

	void update(int playerDeaths, float timeToMax);
	int getScore();
	void resetForNewLevel();
	void init();

private:

	int m_playerDeaths{};
	float m_timeToMax{};
	int m_score{};
	float m_maxTimeToMax;
	int m_maxScore{};

};

