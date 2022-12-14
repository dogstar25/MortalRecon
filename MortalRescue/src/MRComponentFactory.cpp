#include "MRComponentFactory.h"
#include "components/BrainComponent.h"
#include "components/InventoryComponent.h"
#include "components/DroneBrainComponent.h"
#include "components/PistolWeaponComponent.h"


std::shared_ptr<Component> MRComponentFactory::_create(
	Json::Value definitionJSON,
	std::string textComponentGameObjectid,
	Scene* scene,
	float xMapPos,
	float yMapPos,
	float angleAdjust,
	int layer,
	ComponentTypes componentType)
{
	std::shared_ptr<Component> component{};

	auto gameObjectId = definitionJSON["id"].asString();

	//Handle game specific componenets, otherwise call the base ComponentFactory _create
	if (gameObjectId == "DRONE" && componentType == ComponentTypes::BRAIN_COMPONENT) {
		component = std::make_shared<DroneBrainComponent>(definitionJSON);
	}
	else if (gameObjectId == "GINA_64" && componentType == ComponentTypes::WEAPON_COMPONENT) {
		component = std::make_shared<PistolWeaponComponent>(definitionJSON);
	}
	else {
		component = ComponentFactory::_create(
			definitionJSON,
			textComponentGameObjectid,
			scene,
			xMapPos,
			yMapPos,
			angleAdjust,
			layer,
			componentType);
	}

    return component;
}
