#include "MRGame.h"
#include "GameConstants.h"
#include "MRContextManager.h"

using namespace std::chrono_literals;


/*
Initialize Game
*/
bool MRGame::init(std::shared_ptr<ContactListener> contactListener, std::shared_ptr<ContactFilter> contactFilter,
	std::shared_ptr<ComponentFactory> componentFactory, std::shared_ptr<ActionFactory> actionFactory, std::shared_ptr<ParticleEffectsFactory> particleEffectsFactory,
	std::shared_ptr<CutSceneFactory> cutSceneFactory, std::shared_ptr<IMGuiFactory> iMGuiFactory, std::shared_ptr<TriggerFactory> triggerFactory, std::shared_ptr<ContextManager> contextManager,
	std::shared_ptr<EnumMap> enumMap, std::shared_ptr<ColorMap> colorMap)
{

	Game::init(contactListener, contactFilter, componentFactory, actionFactory, particleEffectsFactory, cutSceneFactory, iMGuiFactory, triggerFactory, contextManager, enumMap, colorMap);

	m_gameState = GameState::PLAY;

	//Init font library
	TTF_Init();

	//Initialize the texture manager
	m_renderer->init(m_window);

	//Initialize IMGUI
	ImGui::MobyDickInit(this);

	//Display basic loading message
	_displayLoadingMsg();

	TextureManager::instance().init();
	TextureManager::instance().load("textureAtlasAssets");

	//Initialize the SceneManager
	SceneManager::instance().init();
	SceneManager::instance().load("gameScenes");

	_displayLoadingMsg();

	//Initialize the Game Object Manager
	GameObjectManager::instance().init();
	GameObjectManager::instance().load("gameObjectDefinitions/playerObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/commonObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/wallObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/particleObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/compositeObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/guiObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/hudObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/titleScreenObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/testObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/checkpointObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/enemyObjects");

	_displayLoadingMsg();

	//Initialize the sound manager
	SoundManager::instance().initSound();

	//Load a first scene
	Scene& scene = SceneManager::instance().pushScene("SCENE_TITLE_SCREEN");

	//Initialize the clock object
	Clock::instance().init();

	return true;
}

