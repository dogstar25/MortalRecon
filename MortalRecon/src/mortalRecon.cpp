#include "MRGame.h"
#include "MRContactListener.h"
#include "MRContactFilter.h"
#include "MRComponentFactory.h"
#include "triggers/MRTriggerFactory.h"
#include "cutScenes/MRCutSceneFactory.h"
#include "actions/MRActionFactory.h"
#include "IMGui/MR_IMGuiFactory.h"
#include "particleEffects/MRParticleEffectsFactory.h"
#include "MRContextManager.h"
#include "MREnumMap.h"
#include "MRColorMap.h"
#include <wtypes.h>

std::unique_ptr<Game> game;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
//int main(int argc, char* args[])
{
	//create game 
	game = std::make_unique<MRGame>();

	std::cout << "Mortal Rescue Begins" << std::endl;

	//init game
	game->init(
		std::make_shared<MRContactListener>(), 
		std::make_shared<MRContactFilter>(),
		std::make_shared<MRComponentFactory>(),
		std::make_shared<MRActionFactory>(),
		std::make_shared<MRParticleEffectsFactory>(),
		std::make_shared<MRCutSceneFactory>(),
		std::make_shared<MR_IMGuiFactory>(),
		std::make_shared<MRTriggerFactory>(),
		std::make_shared<MRContextManager>(),
		std::make_shared<MREnumMap>(),
		std::make_shared<MRColorMap>()
	);

	//play game
	game->play();

	return 0;
}