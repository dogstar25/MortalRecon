#include "GameObject.h"


#include "GameObjectManager.h"
#include "game.h"

#include "SceneManager.h"
#include "Scene.h"
#include "components/InventoryComponent.h"
#include "ComponentFactory.h"

#include "Globals.h"
#include "BaseConstants.h"
#include "Camera.h"
#include "EnumMaps.h"


GameObject::~GameObject()
{

}

GameObject::GameObject(std::string gameObjectId, float xMapPos, float yMapPos, float angleAdjust, Scene* parentScene)
{

	Json::Value definitionJSON;

	//Build components
	if (gameObjectId.rfind("DEBUG_", 0) != 0)
	{
		definitionJSON = GameObjectManager::instance().getDefinition(gameObjectId)->definitionJSON();
	}
	else
	{
		definitionJSON = GameObjectManager::instance().getDefinition("DEBUG_ITEM")->definitionJSON();
	}

	//Category Id and Object Type
	m_id = gameObjectId;
	m_collisionTag = EnumMap::instance().toEnum(definitionJSON["collisionTag"].asString());
	m_gameObjectType = EnumMap::instance().toEnum(definitionJSON["type"].asString());
	m_removeFromWorld = false;

	//Trait tags
	for (Json::Value itrControls : definitionJSON["traitTags"])
	{
		uint32_t trait = EnumMap::instance().toEnum(itrControls.asString());
		m_traitTags.set(trait);
	}

	//Set the parent Scene
	m_parentScene = parentScene;

	std::shared_ptr<Component> component{};

	//Always build a render component
	component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::RENDER_COMPONENT);
	addComponent(component, ComponentTypes::RENDER_COMPONENT);

	//Always build a transform component
	component = ComponentFactory::instance().create(definitionJSON, xMapPos, yMapPos, angleAdjust, ComponentTypes::TRANSFORM_COMPONENT);
	addComponent(component, ComponentTypes::TRANSFORM_COMPONENT);

	//Animation Component
	if (definitionJSON.isMember("animationComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::ANIMATION_COMPONENT);
		addComponent(component, ComponentTypes::ANIMATION_COMPONENT);

	}

	//Physics Component
	if (definitionJSON.isMember("physicsComponent"))
	{

		component = ComponentFactory::instance().create(definitionJSON, parentScene, xMapPos, yMapPos, angleAdjust, ComponentTypes::PHYSICS_COMPONENT);
		addComponent(component, ComponentTypes::PHYSICS_COMPONENT);

	}

	//Vitality Component
	if (definitionJSON.isMember("vitalityComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::VITALITY_COMPONENT);
		addComponent(component, ComponentTypes::VITALITY_COMPONENT);

	}

	//Player control Component
	if (definitionJSON.isMember("playerControlComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::PLAYERCONTROL_COMPONENT);
		addComponent(component, ComponentTypes::PLAYERCONTROL_COMPONENT);

	}

	//Text Component
	if (definitionJSON.isMember("textComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, gameObjectId, ComponentTypes::TEXT_COMPONENT);
		addComponent(component, ComponentTypes::TEXT_COMPONENT);

	}

	//Children Component
	if (definitionJSON.isMember("childrenComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, parentScene, ComponentTypes::CHILDREN_COMPONENT);
		addComponent(component, ComponentTypes::CHILDREN_COMPONENT);

	}

	//Action Component
	if (definitionJSON.isMember("actionComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::ACTION_COMPONENT);
		addComponent(component, ComponentTypes::ACTION_COMPONENT);

	}

	//Particle X Component
	if (definitionJSON.isMember("particleXComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::PARTICLE_X_COMPONENT);
		addComponent(component, ComponentTypes::PARTICLE_X_COMPONENT);

	}

	//Simple Particle Component
	if (definitionJSON.isMember("particleComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::PARTICLE_COMPONENT);
		addComponent(component, ComponentTypes::PARTICLE_COMPONENT);

	}

	//Inventory Component
	if (definitionJSON.isMember("inventoryComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, parentScene, ComponentTypes::INVENTORY_COMPONENT);
		addComponent(component, ComponentTypes::INVENTORY_COMPONENT);

	}

	//UIControl Component
	if (definitionJSON.isMember("UIControlComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::UICONTROL_COMPONENT);
		addComponent(component, ComponentTypes::UICONTROL_COMPONENT);

	}

	//Weapon Component
	if (definitionJSON.isMember("weaponComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::WEAPON_COMPONENT);
		addComponent(component, ComponentTypes::WEAPON_COMPONENT);

	}

	//Pool Component
	if (definitionJSON.isMember("poolComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::POOL_COMPONENT);
		addComponent(component, ComponentTypes::POOL_COMPONENT);

	}

	//Composite Component
	if (definitionJSON.isMember("compositeComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, parentScene, ComponentTypes::COMPOSITE_COMPONENT);
		addComponent(component, ComponentTypes::COMPOSITE_COMPONENT);

	}

	//Brain Component
	if (definitionJSON.isMember("brainComponent"))
	{
		component = std::static_pointer_cast<BrainComponent>(ComponentFactory::instance().create(definitionJSON, ComponentTypes::BRAIN_COMPONENT));
		addComponent(component, ComponentTypes::BRAIN_COMPONENT);
	}

	//Navigation Component
	if (definitionJSON.isMember("navigationComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, ComponentTypes::NAVIGATION_COMPONENT);
		addComponent(component, ComponentTypes::NAVIGATION_COMPONENT);

	}

	//Attachments Component
	if (definitionJSON.isMember("attachmentsComponent"))
	{
		component = ComponentFactory::instance().create(definitionJSON, parentScene, ComponentTypes::ATTACHMENTS_COMPONENT);
		addComponent(component, ComponentTypes::ATTACHMENTS_COMPONENT);

	}

}

void GameObject::setPosition(float x, float y)
{

	getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT)->setPosition(x, y);

}

void GameObject::setPosition(b2Vec2 position, float angle)
{
	//-1 means don't apply the angle
	if (angle != -1)
	{
		getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT)->setPosition(position, angle);
	}
	else
	{
		getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT)->setPosition(position);
	}

}


void GameObject::update()
{

	for (auto& component : m_components)
	{
		if (component) {
			component->update();
		}
	}

}


void GameObject::render()
{

	//Render yourself
	getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT)->render();
		
	//Render your children
	if (hasComponent(ComponentTypes::CHILDREN_COMPONENT)){

		getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT)->renderChildren();
	}

	//Render your attached inventory items
	if (hasComponent(ComponentTypes::ATTACHMENTS_COMPONENT)) {

		getComponent<AttachmentsComponent>(ComponentTypes::ATTACHMENTS_COMPONENT)->render();
	}

	//If you have an arcade particle emitter then render those particles
	if (hasComponent(ComponentTypes::PARTICLE_COMPONENT)) {

		getComponent<ParticleComponent>(ComponentTypes::PARTICLE_COMPONENT)->render();
	}

	//If you have a composite component, then render the composite pieces
	if (hasComponent(ComponentTypes::COMPOSITE_COMPONENT)) {

		getComponent<CompositeComponent>(ComponentTypes::COMPOSITE_COMPONENT)->render();
	}



}

void GameObject::reset()
{
	if (hasComponent(ComponentTypes::POOL_COMPONENT)) {
		getComponent<PoolComponent>(ComponentTypes::POOL_COMPONENT)->reset();
	}
	if (hasComponent(ComponentTypes::PHYSICS_COMPONENT)) {
		getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT)->setOffGrid();
	}

}

void GameObject::addInventoryItem( GameObject* gameObject)
{
	//size_t itemCount = getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT)->addItem(gameObject);
	//If this is the only inventory item, then attach it to the player of whatever object this is
	/*if (itemCount == 1)
	{
		getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT)->attachItem(gameObject);
	}*/

}

/*
Execute certain initialization that needs to happen AFTER all components have been constructed and
the GameObject has been emplace/constructed into the collection
*/
void GameObject::init(bool cameraFollow)
{

	//Set the root gameObject as the parent for each component
	for (auto& component : m_components) {
		if (component) {
			component->setParent(this);
		}
	}

	//Set the Physics component gameObject UserData
	if (hasComponent(ComponentTypes::PHYSICS_COMPONENT)) {
		auto physicsComponent = getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
		physicsComponent->physicsBody()->SetUserData(this);

	}

	//If we specified that the camera follow this gameobject then tell the camera
	if (cameraFollow) {
		Camera::instance().setFollowMe(this);
	}

	//NEW - execute special code for certain extra complicated gameObjects that need to execute after main construction
	//if (id() == "GINA_64") {

	//	//ToDo:Move to postinit for Inventory/attachment components
	//	const auto& playerInventoryComponent = getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
	//	playerInventoryComponent->weldOnAttachments();
	//}

	
}

void GameObject::setPhysicsActive(bool active)
{

	const auto& physicsComponent = getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	if (physicsComponent) {
		physicsComponent->setPhysicsBodyActive(active);
	}

}

void GameObject::setAngleInRadians(float angle)
{

	const auto& physicsComponent = getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	if (physicsComponent) {

		physicsComponent->setAngle(angle);
	}

}

void GameObject::setAngleInDegrees(float angle)
{

	const auto& physicsComponent = getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	if (physicsComponent) {

		angle = util::degreesToRadians(angle);

		physicsComponent->setAngle(angle);
	}

}

/*
The postInit function allows gameobjects to initilaize it's components that require ALL gameObjects to be built first.
ex. The brainComponent needs all navigation related gameObjects to be built first
*/
void GameObject::postInit(const std::array <std::vector<std::shared_ptr<GameObject>>, MAX_GAMEOBJECT_LAYERS>& gameObjectCollection)
{

	//GameObjects with a NavigationComponent needs to build a navigation array based on the location of 
	//other navigation objects
	if (hasComponent(ComponentTypes::NAVIGATION_COMPONENT)) {
		const auto navigationComponent = getComponent<NavigationComponent>(ComponentTypes::NAVIGATION_COMPONENT);
		navigationComponent->postInit();
	}

	//The BrainComponent needs to gather and store all of the waypoint nav points and
	//interim nav points for its navigating logic
	if (hasComponent(ComponentTypes::BRAIN_COMPONENT)) {
		const auto brainComponent = getComponent<BrainComponent>(ComponentTypes::BRAIN_COMPONENT);
		brainComponent->postInit();
	}

	//The CompositeComponent needs to weld on its component pieces it the weld flag is turned on
	if (hasComponent(ComponentTypes::COMPOSITE_COMPONENT)) {
		const auto compositeComponent = getComponent<CompositeComponent>(ComponentTypes::COMPOSITE_COMPONENT);
		compositeComponent->postInit();
	}

	//The Attachments component needs to weld on attachment objects as well as potentially add the 
	// attchement object to the inventory component
	if (hasComponent(ComponentTypes::ATTACHMENTS_COMPONENT)) {
		const auto attachmentsComponent = getComponent<AttachmentsComponent>(ComponentTypes::ATTACHMENTS_COMPONENT);
		attachmentsComponent->postInit();
	}


}

void GameObject::setParentScene(Scene* parentScene)
{
	m_parentScene = parentScene;
}

SDL_FPoint GameObject::getCenterPosition()
{

	const auto& transformComponent = getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
	return(transformComponent->getCenterPosition());

}
