#pragma once
#include "MobyDick.h"

class MRTriggerFactory : public TriggerFactory
{
public:
	MRTriggerFactory();

	std::shared_ptr<Trigger> create(std::string triggerType) override;

private:

};

