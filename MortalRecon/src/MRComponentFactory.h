#pragma once
#include "MobyDick.h"

class Scene;

class MRComponentFactory : public ComponentFactory
{

public:


private:
	//Create version that has ALL possible inputs
	std::shared_ptr<Component> create(
		Json::Value definitionJSON,
		std::string gameObjectName,
		std::string gameObjectTextType,
		Scene* scene,
		float xMapPos,
		float yMapPos,
		float angleAdjust,
		const int componentType) override;

};

