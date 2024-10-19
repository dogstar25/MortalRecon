#pragma once
#include "MobyDick.h"

class PistolFireAction : public Action
{
public:
	PistolFireAction() = default;

	void perform(GameObject* gameObject, b2Vec2 destination) override;

private:

};

