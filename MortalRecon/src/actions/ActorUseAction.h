#pragma once
#include "MobyDick.h"

class GameObject;

class ActorUseAction : public UseAction
{
public:

	ActorUseAction() = default;

	void perform(GameObject* gameObject, int usageParm, b2Vec2 destination) override;

};
