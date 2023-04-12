#include "MRCutSceneFactory.h"
#include "CutSceneDiscoverTreasure.h"


std::shared_ptr<CutScene> MRCutSceneFactory::create(std::string cutSceneType)
{
	std::shared_ptr<CutScene> cutScene;

	if (cutSceneType == "CutSceneDiscoverTreasure") {

		cutScene = std::make_shared<CutSceneDiscoverTreasure>();
	}
	else {

		assert(false && "CuteScene Types was not found");
	}

	return cutScene;
}
