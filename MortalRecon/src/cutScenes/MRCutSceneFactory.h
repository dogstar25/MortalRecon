#pragma once
#include "MobyDick.h"

class MRCutSceneFactory : public CutSceneFactory
{
public:
	
	std::shared_ptr<CutScene> create(std::string cutSceneType);

private:

};
