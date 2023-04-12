#pragma once
#include "MobyDick.h"

class OnetimeButtonInteraction : public Action
{

	void perform(GameObject* interactingObject, GameObject* interactionObject, SDL_Scancode keyCode) override;


};

