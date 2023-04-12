#pragma once
#include "MobyDick.h"

class ActorRotateAction : public Action
{

public:
	ActorRotateAction() = default;

	void perform(GameObject* gameObject, float angularVelocity) override;


};

