#include "MRContextManager.h"
#include "SoundManager.h"
#include "Util.h"
#include "game.h"

extern std::unique_ptr<Game> game;

MRContextManager::MRContextManager()
	: ContextManager()
{
	initMappings();

	SaveFileData saveFileData;

	//Get the saved values from gameData file or create the gameData file for the first time
	if (util::fileExists(GAME_FILENAME)) {

		loadGame(saveFileData);

	}
	else {

		
		saveFileData.level = 1;
		saveFileData.mouseSensitivity = 50;
		saveFileData.soundLevel = 50;
		saveGame(saveFileData);

	}

}

void MRContextManager::initMappings()
{

	m_statusValueMap["LIVES_COUNT"] = StatusItem{6, 6};
	m_statusValueMap["SCRAP_COUNT"] = StatusItem{ 0, 50 };

}

bool MRContextManager::loadGame(SaveFileData& saveFileData)
{
	std::ifstream m_gameFile(GAME_FILENAME, std::ofstream::in);

	m_gameFile.read(reinterpret_cast<char*>(&saveFileData), sizeof(saveFileData));

	m_gameFile.close();
	if (!m_gameFile) {
		std::cout << "Error reading game file" << std::endl;
		return false;
	}

	//set values for the settings
	m_userSettings.mouseSensitivity = saveFileData.mouseSensitivity;
	m_userSettings.soundLevel = saveFileData.soundLevel;

	return true;

}

bool MRContextManager::saveGame(SaveFileData& saveFileData)
{

	std::ofstream m_gameFile(GAME_FILENAME, std::ofstream::out);

	m_gameFile.write(reinterpret_cast<char*>(&saveFileData), sizeof(saveFileData));

	m_gameFile.close();
	if (!m_gameFile) {
		std::cout << "Error writing game file" << std::endl;
		return false;
	}

	game->contextMananger()->setMouseSensitivity(saveFileData.mouseSensitivity);
	game->contextMananger()->setSoundVolume(saveFileData.soundLevel);

	return true;
}

