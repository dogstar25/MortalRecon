#pragma once
#include "MobyDick.h"

class EnemyADeadTrigger : public Trigger
{

public:
	EnemyADeadTrigger();
	bool hasMetCriteria(Scene* scene) override;
	void execute() override;
};

