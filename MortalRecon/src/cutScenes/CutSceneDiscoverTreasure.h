#pragma once
#include "MobyDick.h"

class CutSceneDiscoverTreasure : public CutScene
{

public:
	void run(Scene* scene) override;
	void start() override;
	void update() override;
	void end() override;

private:

	int m_currentAct{ 1 };
	int m_numberOfActs{ 2 };

	std::weak_ptr<GameObject> _player;
	std::weak_ptr<GameObject> _frank;
	Timer scene1Timer{};

	std::shared_ptr<GameObject> _startPlayer();
	std::shared_ptr<GameObject> _startFrank();

	void _endFrank();
	void _endPlayer();


	



};
