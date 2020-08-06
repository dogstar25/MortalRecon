#include "SceneManager.h"

#include <fstream>

#include "game.h"
#include "Renderer.h"
#include "Clock.h"


SceneManager::SceneManager()
{
	m_currentSceneIndex = 0;
}

SceneManager::~SceneManager()
{

}

SceneManager& SceneManager::instance()
{

	static SceneManager singletonInstance;
	return singletonInstance;

}

void SceneManager::init()
{
	load("gameScenes");
}

void SceneManager::load(std::string sceneDefinitionsFilename)
{

	//Read file and stream it to a JSON object
	Json::Value root;
	std::string filename = "assets/config/" + sceneDefinitionsFilename + ".json";
	std::ifstream ifs(filename);
	ifs >> root;

	for (Json::Value itr : root["scenes"])
	{
		std::string gameObjectId = itr["id"].asString();


		auto maxObjects = itr["maxObjects"].asInt();

		//Json::Value sceneJSON = Json::Value(itr);
		m_sceneDefinitions.emplace(gameObjectId, Json::Value(itr));
	}
}

//Scene* SceneManager::addScene()
//{
//
//	return m_scenes.emplace(std::make_unique<Scene>()).get();
//	//scene = nullptr;
//
//}

//void SceneManager::addScene(std::unique_ptr<Scene> scene)
//{
//
//	m_scenes.emplace(std::move(scene));
//
//}


void SceneManager::pushIntroScene()
{

	Scene& scene = SceneManager::instance().scenes().emplace_back("GAMESCENE_INTRO");

	scene.init(MOUSE_MODE_CONTROLLER, "level1", SDLK_UNKNOWN, 1000);
	scene.addGameObject("BOWMAN", LAYER_MAIN, 4, 4, 0);
	scene.addGameObject("SWORDLADY", LAYER_MAIN, 8, 8, 0);
	scene.addGameObject("GINA_64", LAYER_MAIN, 8, 8, 0);

	SceneAction sceneAction = { SCENE_ACTION_ADD , "GAMESCENE_PAUSE_MENU" };
	scene.addKeyAction(SDLK_ESCAPE, sceneAction);
	//scene.addKeyAction(SDLK_ESCAPE, { SceneActionCode::NEW , "GAMESCENE_PAUSE_MENU" });


}

void SceneManager::pushPauseMenuScene()
{
	Scene& scene = SceneManager::instance().scenes().emplace_back("GAMESCENE_PAUSE_MENU");
	scene.init(MOUSE_MODE_NAVIGATE, "", SDLK_ESCAPE,  32);
	scene.addGameObject("GUIPausePanel", LAYER_MAIN, 4, 4, 0);

	SceneAction sceneAction = { SCENE_ACTION_EXIT , "" };
	scene.addKeyAction(SDLK_ESCAPE, sceneAction);


}


void SceneManager::run()
{


	//Capture the amount of time that has passed since last loop and accumulate time for both
	//the FPS calculation and the game loop timer
	Clock::instance().update();

	//Only update and render if we have passed the 60 fps time passage
	if (Clock::instance().hasMetGameLoopSpeed())
	{

		//Update only the scenes that are not paused
		for (auto& scene : m_scenes) {
			if (scene.state() == SceneState::RUN) {
				scene.update();
			}
		}

		//Render All scenes
		Renderer::instance().clear();

		for (auto& scene : m_scenes) {
			scene.render();
		}

		Renderer::instance().present();

		//Increment frame counter and calculate FPS and reset the gameloop timer
		Clock::instance().calcFps();

	}

}

std::optional<SceneAction> SceneManager::pollEvents()
{
	int keyCode, scanCode, keyCount, keyStateCount;
	SDL_Event event;
	//PlayerInputEvent* playerInputEvent = nullptr;
	const Uint8* keyStates = nullptr;
	std::optional<SceneAction> sceneAction;

	//Handle special events and everything else should be player control
	//input related so staore it for later
	while (SDL_PollEvent(&event) && sceneAction.has_value() == false)
	{
		switch (event.type)
		{
			case SDL_KEYUP:
			case SDL_KEYDOWN:
			{
				keyCode = event.key.keysym.sym;

				/*
				Translate the keycode to whatever action it is tied to in this scene
				Only interested in KEYDOWN for sceneActions
				*/
				if (event.type == SDL_KEYDOWN) {
					sceneAction = getSceneKeyAction(keyCode);
				}

				/*
				If no mapping was found for the keycode, then assume that
				it is player movement related and store it for later
				*/
				if (sceneAction.has_value() == false) {
					PlayerInputEvent& playerInputEvent = m_PlayerInputEvents.emplace_back();
					playerInputEvent.event = event;

					//Get the keyboard state array and copy it to our save spot - memcpy!!!
					keyStates = SDL_GetKeyboardState(&keyStateCount);
					memcpy_s(playerInputEvent.keyStates,
						SDL_NUM_SCANCODES * sizeof(unsigned char),
						keyStates,
						keyStateCount * sizeof(unsigned char));
				}

				break;
			}
			case SDL_USEREVENT:
			{
				//std::optional<SceneActionCode*> actionCode = (SceneActionCode*)event.user.data1;
				sceneAction = *(static_cast<std::optional<SceneAction>*>(event.user.data1));
				delete event.user.data1;
				break;
			}
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			{
				PlayerInputEvent& playerInputEvent = m_PlayerInputEvents.emplace_back();
				playerInputEvent.event = event;

				break;
			}
			default:
				break;


		}


	}

	return sceneAction;


}

std::optional<SceneAction> SceneManager::getSceneKeyAction(SDL_Keycode keycode)
{
	return m_scenes.back().getkeycodeAction(keycode);
}

void SceneManager::popScene()
{

	m_scenes.pop_back();
	m_scenes.back().setState(SceneState::RUN);

}

Scene& SceneManager::pushScene(std::string sceneId)
{
	if (m_scenes.empty() == false) {
		m_scenes.back().setState(SceneState::PAUSE);
	}
	Scene& scene = SceneManager::instance().scenes().emplace_back(sceneId);

	return scene;
	
}

