#pragma once
#include "GameObject.h"

enum worldObjectCategory {
	GENERIC = 1,
	PLAYER = 2,
	WALL = 4,
	PLAYER_BULLET = 8,
	PARTICLE1 = 16,
	PARTICLE2 = 32,
	PARTICLE3 = 64,
	ENEMY_FRAME = 128,
	ENEMY_ARMOR = 256
};

class WorldObject :	public GameObject
{
public:
	WorldObject();
	WorldObject(string,int,int,int);
	~WorldObject();

	void update();
	void render();
	void setPosition(b2Vec2, float);
	SDL_Rect  getRenderDestRect();

	b2Body* buildB2Body(GameObjectDefinition*);
	uint16 setCollisionMask(uint16 category);

	b2Body* physicsBody;

	float speed;
};

