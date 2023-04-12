#pragma once
#include "MobyDick.h"

class SurvivorBrainComponent : public BrainComponent
{

	

public:
	SurvivorBrainComponent(Json::Value definitionJSON);


	void update() override;
	void followMe(std::shared_ptr<GameObject> gameObjectToFollow);
	void stay();

	const int SURVIVOR_FOLLOW_TOLERANCE = 90;

private:

	int _determineState();
	void _doFollow();
	void _doLost();
	void _doIdle();
	void _doEscape();
	bool _rotateTowards(b2Vec2 targetPoint);
	std::optional<SDL_FPoint> _detectPlayer();
	bool _detectFollowedObject();
	bool _detectEscapeLocation();
	void _stayBehindFollowedObject();
	bool _isTouchingBarrier();

	std::weak_ptr<GameObject> m_gameObjectToFollow{};
	std::optional<SDL_FPoint> m_escapeLocation{};
	Timer m_lostTimer;




};
