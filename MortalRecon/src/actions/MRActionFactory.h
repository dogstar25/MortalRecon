#pragma once
#include "MobyDick.h"

class MRActionFactory : public ActionFactory{



public:

	std::shared_ptr<Action> create(std::string actionType) override;


private:




};
