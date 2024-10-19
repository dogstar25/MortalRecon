#pragma once
#include "C:\projects\MobyDick-1.0\MobyDick\src\actions\Action.h"
class ActorRotateDirectAngleAction : public Action
{

public:
	ActorRotateDirectAngleAction() = default;

	void perform(GameObject* gameObject, float angularVelocity) override;



};

