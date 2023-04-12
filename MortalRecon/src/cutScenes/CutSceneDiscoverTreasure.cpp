#include "CutSceneDiscoverTreasure.h"

extern std::unique_ptr<Game> game;


/*
Example cutscene
*/
void CutSceneDiscoverTreasure::run(Scene* scene)
{
	currentScene = scene;

	if (currentState == cutSceneState::IDLE) {

		start();
	}
	else if (currentState == cutSceneState::RUNNING) {

		update();

	}

}

void CutSceneDiscoverTreasure::start()
{

	currentState = cutSceneState::RUNNING;

	//_saveCurrentState();

	if (m_currentAct == 1) {

		//Get the player and disable the player controls
		_startPlayer();

		//Get Frank, give Frank a brain, and dispatch Frank to a destination
		_frank = _startFrank();

		const auto& navComponent = _frank.lock()->getComponent<NavigationComponent>(ComponentTypes::NAVIGATION_COMPONENT);
		navComponent->navigateTo(5400,900);

		Camera::instance().setFollowMe(_frank.lock());

		scene1Timer = Timer(1500);

	}
	else if (m_currentAct == 2) {

		//_frank->dispatch({ 1,1 });
		const auto& navComponent = _frank.lock()->getComponent<NavigationComponent>(ComponentTypes::NAVIGATION_COMPONENT);
		navComponent->navigateTo(5400, 900);

		Camera::instance().dispatch({ 4000,900 });
	}

}

void CutSceneDiscoverTreasure::update()
{

	const auto& brainComponent = _frank.lock()->getComponent<BrainComponent>(ComponentTypes::BRAIN_COMPONENT);
	auto franksBrainState = brainComponent->state();

	if (m_currentAct == 1) {
		if (franksBrainState == BrainState::IDLE &&
			scene1Timer.hasMetTargetDuration() == true) {
			currentState = cutSceneState::IDLE;
			m_currentAct += 1;
		}
	}
	else if (m_currentAct == 2) {
		if (franksBrainState == BrainState::IDLE &&
			Camera::instance().state() == CameraState::IDLE) {
			currentState = cutSceneState::IDLE;
			m_currentAct += 1;
		}
	}

	if (m_currentAct > m_numberOfActs) {
		end();
	}

}

void CutSceneDiscoverTreasure::end()
{

	//Call the wrapup functions for the pieces
	_endFrank();
	_endPlayer();

	//Create the event that will trigger the end of the scene to the sceneManager
	util::sendSceneEvent(SCENE_ACTION_RELEASE_DIRECT);

}

std::shared_ptr<GameObject> CutSceneDiscoverTreasure::_startPlayer()
{
	auto playerObject = SceneManager::instance().currentScene().getGameObjectsByName("PlayerGina");
	assert(!playerObject.empty() && "GameObject wasnt found!");

	//There shoudl only be one player
	auto _player = playerObject[0];
	_player->getComponent<PlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT)->disable();

	return _player;
}

void CutSceneDiscoverTreasure::_endPlayer()
{
	_player.lock()->getComponent<PlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT)->enable();
	
}

std::shared_ptr<GameObject> CutSceneDiscoverTreasure::_startFrank()
{

	Json::Value componentsDefinition{};
	Json::Value brainDefinition{};

	auto frankGameObjects = SceneManager::instance().currentScene().getGameObjectsByName("Frank");
	assert(!frankGameObjects.empty() && "GameObject wasnt found!");

	//There shoudl only be one frank
	auto frank = frankGameObjects[0];

	//Give Frank a brain
	//brainDefinition["id"] = "BRAIN_COMPONENT";
	//brainDefinition["sightSensorSize"] = 25;
	//componentsDefinition["components"].append(brainDefinition);

	//const auto& brainComponent =
	//	std::static_pointer_cast<BrainComponent>(
	//		game->componentFactory()->create(componentsDefinition, "Frank","SURVIVOR", currentScene, 0, 0, 0, ComponentTypes::BRAIN_COMPONENT)
	//		);
	//brainComponent->setParent(frank);
	//frank->addComponent(brainComponent, ComponentTypes::BRAIN_COMPONENT);

	return frank;

}

void CutSceneDiscoverTreasure::_endFrank()
{



}
