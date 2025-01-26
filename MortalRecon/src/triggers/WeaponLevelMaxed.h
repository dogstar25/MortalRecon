#pragma once
#include "MobyDick.h"

class WeaponLevelMaxed :  public Trigger
{

public:
	WeaponLevelMaxed();
	bool hasMetCriteria(Scene* scene) override;
	void execute() override;

};

