#pragma once

#include <string>

#include <box2d/box2d.h>
#include <SDL2/SDL.h>


/*
Particle Effect struct is initialized with values if you do not want to override
*/
struct ParticleEffect {
	std::string poolId = "SMOKE1_POOL";
	b2Vec2 originMin;
	b2Vec2 originMax;
	int forceMin = 50;
	int forceMax = forceMin;
	float lifetimeMin = 2.5;
	float lifetimeMax = 2.5;
	bool alphaFade = true;
	float angleMin = 0;
	float angleMax = 360;
	float particleSizeMin = 1;
	float particleSizeMax = 1;
	SDL_Color colorRangeBegin = {255,255,255,255};
	SDL_Color colorRangeEnd = { 255,255,255,255 };
	int particleSpawnCountMin = 25;
	int particleSpawnCountMax = 25;
};

namespace ParticleEffects {

	static const ParticleEffect ricochet = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 5,
		.forceMax = 5,
		.lifetimeMin = 2.0F,
		.lifetimeMax = 2.0F,
		.alphaFade = false,
		.angleMin = 0,
		.angleMax = 360,
		.particleSizeMin = 10.28F,
		.particleSizeMax = 20.50F,
		.colorRangeBegin = {0,0,0,255},
		.colorRangeEnd = {255,255,255,255},
		.particleSpawnCountMin = 5,
		.particleSpawnCountMax = 25
	};
}