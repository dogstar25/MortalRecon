#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include <cstddef>

#include "Animation.h"

using namespace std;

struct TextDetails {

	SDL_Color color;
	int size;
	bool isDynamic;
	string fontId;
	string label;

};

class GameObjectDefinition
{
public:

	GameObjectDefinition();
	~GameObjectDefinition();

	string
		id,
		description,
		physicsType,
		collisionShape,
		textureId;
	float
		xSize,
		ySize,
		speed,
		friction,
		restitution,
		density,
		linearDamping,
		collisionRadius,
		angularDamping,
		lifetime;
	bool
		isAnimated,
		isPhysicsObject,
		isPrimitiveShape,
		isPlayerObject,
		isTextObject,
		isParticle;
	short
		collisionGroup; // objects with same negative group value will not collide

	TextDetails textDetails;
	SDL_Color primativeColor; //If object is a primative shape, what color is it
	map<string, Animation*> animations;


};