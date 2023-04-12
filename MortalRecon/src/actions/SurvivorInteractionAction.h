#pragma once
#include "MobyDick.h"

class SurvivorInteractionAction : public Action
{

	void perform(GameObject* interactingObject, GameObject* interactionObject , SDL_Scancode keyCode) override;


};

