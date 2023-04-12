#pragma once
#include "MobyDick.h"

class TurretFireAction : public Action
{
public:
	TurretFireAction() = default;

	void perform(GameObject* gameObject) override;

private:

};

