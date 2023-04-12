#pragma once
#include "MobyDick.h"

class DroneEyeRotateAction : public Action
{

public:
	DroneEyeRotateAction() = default;

	void perform(GameObject* gameObject, float angularVelocity) override;


};