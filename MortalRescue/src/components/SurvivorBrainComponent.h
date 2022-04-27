#pragma once
#pragma once
#include "components\BrainComponent.h"

#include <iostream>
#include <optional>
#include <json/json.h>

#include "Timer.h"

class SurvivorBrainComponent : public BrainComponent
{

public:
	SurvivorBrainComponent(Json::Value definitionJSON);

	void update() override;
	void followMe(GameObject* gameObjectToFollow);
	//void postInit() override;

private:

	int _determineState();
	void _doFollow();
	void _doEngage();
	void _doIdle();
	bool _rotateTowards(b2Vec2 targetPoint);
	std::optional<SDL_FPoint> _detectPlayer();

	GameObject* m_gameObjectToFollow{};




};