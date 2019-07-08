#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <json/json.h>
#include <stdio.h>
#include <string>
#include <map>
#include <Box2D/Box2D.h>

#include "GameObject.h"
#include "SDL_ttf.h"

//Forward declarations
class GameObject;
class Texture;
class PlayerObject;
class WorldObject;
class TextObject;
class Game;

using namespace std;

extern Game* game;

class TextureManager
{

public:

	TextureManager();
	~TextureManager();

	bool init(SDL_Window*);
	void render(WorldObject* gameObject);
	void render(PlayerObject* gameObject);
	void render(GameObject* gameObject);
	void render(TextObject* gameObject);
	void renderTextTexture(SDL_Texture*, float, float);
	bool present();
	bool clear();
	Texture* getTexture(string id);
	Texture* getTexture(GameObject*);
	void addTexture(string, Texture*);
	string getFont(string id);

	Texture* updateDynamicTextTexture(TextObject*);
	SDL_Surface* generateTextSurface(SDL_Color, int, string, string);
	Texture* generateTextTexture(GameObject*, string newText= std::string());
	void drawPoly(b2Body* body);
	void drawPoints(SDL_Point *);
	void drawLine(b2Vec2, b2Vec2);

private:

	SDL_Renderer* pRenderer;
	map<string, unique_ptr<Texture>> textureMap;
	map<string, string> fontMap;
	bool loadTextures();
	
};

class Texture
{
public:

	SDL_Texture* sdlTexture;
	SDL_Surface* surface;

};

