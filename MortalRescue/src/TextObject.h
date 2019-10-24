#pragma once
#include "GameObject.h"

extern Game* game;


class TextObject :	public GameObject
{
public:
	TextObject();
	TextObject(string, int, int, int);
	virtual ~TextObject();

	void update();
	void render();
	SDL_Rect* getRenderDestRect(SDL_Rect* );

	bool isDynamic;
	string fontId;
	string textValue;
		

};
