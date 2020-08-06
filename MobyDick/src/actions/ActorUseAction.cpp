#include "ActorUseAction.h"

#include <memory>

#include "../components/InventoryComponent.h"
#include "../components/ActionComponent.h"
#include "../GameObject.h"

ActorUseAction::ActorUseAction()
{

}

ActorUseAction::~ActorUseAction()
{


}

/*
The Actores UseAction is usually to Perform the UseAction of the Actor's activeItem from his inventory
*/
void ActorUseAction::perform(GameObject* gameObject)
{
	//Get the Actores inventory component
	const auto& inventoryComponent = gameObject->getComponent<InventoryComponent>();

	//Get active inventory item 
	if (const auto& item = inventoryComponent->items()[inventoryComponent->activeItem()].lock())
	{
		//Perform the UseAction of this item
		//item->getComponent<ActionComponent>()->useAction(item.get());
		//item->getComponent<ActionComponent>()->perform();
	}



}