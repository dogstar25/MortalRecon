#include "ActorUseAction.h"

/*
The Actors UseAction is usually to Perform the UseAction of the Actor's activeItem from his inventory
*/
void ActorUseAction::perform(GameObject* gameObject, int usageParm, b2Vec2 destination)
{
	//Get the Actores inventory component
	const std::shared_ptr<InventoryComponent> inventoryComponent = gameObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

	//Get active inventory item 
	if (const auto item = inventoryComponent->getActiveItem())
	{
		//Perform the UseAction of this item
		const auto& itemActionComponent = item->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
		const auto&  action = itemActionComponent->getAction(usageParm);

		//Is this the special usage secondary fire or the normal fire
		if (usageParm == ACTION_USAGE_SPECIAL) {
			action->perform(item);
		}
		else if (usageParm == ACTION_USAGE) {
			action->perform(item, destination);
		}
	}


}