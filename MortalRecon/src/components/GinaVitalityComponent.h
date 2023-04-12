#pragma once
#include "MobyDick.h"

class GinaVitalityComponent : public VitalityComponent
{
public:
	GinaVitalityComponent();
	GinaVitalityComponent(Json::Value componentJSON);
	~GinaVitalityComponent();

	void update() override;
};
