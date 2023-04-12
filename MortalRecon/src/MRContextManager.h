#pragma once

#include "MobyDick.h"

class GameSaveFileData : public BaseSaveFileData {
	public:
	short level;
};

class MRContextManager : public ContextManager
{

public:
	//static MRContextManager& instance();
	MRContextManager();

	bool saveGame(BaseSaveFileData* saveFileData) override;
	bool loadGame(BaseSaveFileData* saveFileData) override;
	int getCurrentLevel();



};

																																																																																																																	