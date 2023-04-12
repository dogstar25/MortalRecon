#pragma once

#include "MobyDick.h"

class GameObject;

class ActorUseAction : public UseAction
{
public:

	ActorUseAction() = default;

	void perform(GameObject* gameObject, int usageParm) override;

};

