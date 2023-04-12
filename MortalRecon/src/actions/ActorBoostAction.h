#pragma once
#include "MobyDick.h"

class ActorBoostAction : public Action
{

public:
	ActorBoostAction() = default;

	void perform(GameObject* gameObject) override;

};