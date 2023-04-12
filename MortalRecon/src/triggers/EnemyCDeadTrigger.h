#pragma once
#include "MobyDick.h"

class EnemyCDeadTrigger : public Trigger
{

public:
	EnemyCDeadTrigger();
	bool hasMetCriteria(Scene* scene) override;
	void execute() override;
};

