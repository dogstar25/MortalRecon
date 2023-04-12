#pragma once

#include "MobyDick.h"

namespace ParticleEffects {

	static const ParticleEffect ricochet = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 5,
		.forceMax = 15,
		.lifetimeMin = 0.1F,
		.lifetimeMax = 1.2F,
		.alphaFade = true,
		.angleMin = 0,
		.angleMax = 360,
		.particleSizeMin = 1.F,
		.particleSizeMax = 10.F,
		.colorRangeBegin = {200,200,200,255},
		.colorRangeEnd = {255,255,255,255},
		.particleSpawnCountMin = 5,
		.particleSpawnCountMax = 10
	};

	static const ParticleEffect deflect = {
		.poolId = "DEFLECT1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 1,
		.forceMax = 6,
		.lifetimeMin = 0.5F,
		.lifetimeMax = 0.5F,
		.alphaFade = true,
		.angleMin = 0,
		.angleMax = 360,
		.particleSizeMin = 32.0F,
		.particleSizeMax = 64.0F,
		//.colorRangeBegin = {0,0,0,255},
		//.colorRangeEnd = {255,255,255,255},
		.particleSpawnCountMin = 1,
		.particleSpawnCountMax = 2
	};

	static const ParticleEffect scrap = {
		.poolId = "SCRAP1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 2,
		.forceMax = 15,
		.lifetimeMin = 0.0F,
		.lifetimeMax = 0.0F,
		.alphaFade = false,
		.angleMin = 0,
		.angleMax = 360,
		.particleSizeMin = 8.F,
		.particleSizeMax = 8.F,
		.colorRangeBegin = {0,0,0,255},
		.colorRangeEnd = {255,255,255,255},
		.particleSpawnCountMin = 2,
		.particleSpawnCountMax = 2
	};

	static const ParticleEffect spark = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 1,
		.forceMax = 5,
		.lifetimeMin = 0.2F,
		.lifetimeMax = 1.5F,
		.alphaFade = true,
		.angleMin = 90,
		.angleMax = 90,
		.particleSizeMin = 1.F,
		.particleSizeMax = 3.F,
		.colorRangeBegin = {255,0,0,255},
		.colorRangeEnd = {255,0,0,255},
		.particleSpawnCountMin = 2,
		.particleSpawnCountMax = 70
	};

	static const ParticleEffect jetpack = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 0,
		.forceMax = 4,
		.lifetimeMin = 0.2F,
		.lifetimeMax = 0.5F,
		.alphaFade = true,
		.angleMin = 180,
		.angleMax = 180,
		.particleSizeMin = 10.F,
		.particleSizeMax = 20.F,
		.colorRangeBegin = {0,0,0,255},
		.colorRangeEnd = {255,0,0,255},
		.particleSpawnCountMin = 2,
		.particleSpawnCountMax = 4
	};

	static const ParticleEffect jetpack_sparks = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 4,
		.forceMax = 14,
		.lifetimeMin = 0.2F,
		.lifetimeMax = 0.5F,
		.alphaFade = true,
		.angleMin = 170,
		.angleMax = 190,
		.particleSizeMin = 5.F,
		.particleSizeMax = 5.F,
		.colorRangeBegin = {255,255,255,50},
		.colorRangeEnd = {255,255,255,100},
		.particleSpawnCountMin = 2,
		.particleSpawnCountMax = 20
	};

	static const ParticleEffect impactSmoke = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 5,
		.forceMax = 10,
		.lifetimeMin = 0.1F,
		.lifetimeMax = 2.2F,
		.alphaFade = true,
		.angleMin = 0,
		.angleMax = 360,
		.particleSizeMin = 1.F,
		.particleSizeMax = 10.F,
		.colorRangeBegin = {255,255,255,255},
		.colorRangeEnd = {255,255,255,255},
		.particleSpawnCountMin = 2,
		.particleSpawnCountMax = 5
	};

	static const ParticleEffect meteor = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {4000,4080},
		.forceMin = 1,
		.forceMax = 2,
		.lifetimeMin = 5.2F,
		.lifetimeMax = 35.0F,
		.alphaFade = true,
		.angleMin = 0,
		.angleMax = 360,
		.particleSizeMin = 2.0F,
		.particleSizeMax = 8.0F,
		.colorRangeBegin = {0,0,255,100},
		.colorRangeEnd = {0,0,255,255},
		.particleSpawnCountMin = 15,
		.particleSpawnCountMax = 50
	};

	static const ParticleEffect meteor2 = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {2000,0},
		.forceMin = 25,
		.forceMax = 30,
		.lifetimeMin = 5.2F,
		.lifetimeMax = 10.0F,
		.alphaFade = true,
		.angleMin = 90,
		.angleMax = 90,
		.particleSizeMin = 10.0F,
		.particleSizeMax = 10.0F,
		.colorRangeBegin = {0,255,255,100},
		.colorRangeEnd = {0,255,255,255},
		.particleSpawnCountMin = 0,
		.particleSpawnCountMax = 4
	};

	static const ParticleEffect explosionSmoke = {
		.poolId = "SMOKE1_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 15,
		.forceMax = 40,
		.lifetimeMin = 0.5F,
		.lifetimeMax = 2.5F,
		.alphaFade = true,
		.angleMin = 0,
		.angleMax = 360,
		.particleSizeMin = 2.F,
		.particleSizeMax = 18.F,
		.colorRangeBegin = {200,0,0,150},
		.colorRangeEnd = {255,0,0,255},
		.particleSpawnCountMin = 20,
		.particleSpawnCountMax = 35
	};	

	static const ParticleEffect turretScrap = {
		.poolId = "TURRET_SCRAP_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 20,
		.forceMax = 20,
		.lifetimeMin = 4.0,
		.lifetimeMax = 7.0,
		.alphaFade = true,
		.angleMin = 0,
		.angleMax = 360,
		.particleSizeMin = 16.F,
		.particleSizeMax = 32.F,
		.colorRangeBegin = { 0, 255, 255, 255 },
		.colorRangeEnd = { 0, 255, 255, 255 },
		.particleSpawnCountMin = 2,
		.particleSpawnCountMax = 4
	};

	static const ParticleEffect pulseExplosion = {
			.poolId = "PULSE_EXPLOSION_POOL",
			.originMin = {0,0},
			.originMax = {0,0},
			.forceMin = 0,
			.forceMax = 0,
			.lifetimeMin = 1.0,
			.lifetimeMax = 1.0,
			.alphaFade = false,
			.angleMin = 0,
			.angleMax = 0,
			.particleSizeMin = 32.F,
			.particleSizeMax = 32.F,
			.colorRangeBegin = { 0, 0, 0, 0 },
			.colorRangeEnd = { 0, 0, 0, 0 },
			.particleSpawnCountMin = 1,
			.particleSpawnCountMax = 1
	};

	static const ParticleEffect radiation = {
		.poolId = "RADIATION_POOL",
		.originMin = {0,0},
		.originMax = {0,0},
		.forceMin = 1,
		.forceMax = 5,
		.lifetimeMin = 2.2F,
		.lifetimeMax = 4.5F,
		.alphaFade = false,
		.angleMin = 30,
		.angleMax = 145,
		.particleSizeMin = 5.1,
		.particleSizeMax = 20.2,
		.colorRangeBegin = {180,0,0,255},
		.colorRangeEnd = {255,30,76,255},
		.particleSpawnCountMin = 20,
		.particleSpawnCountMax = 40
	};

	static const ParticleEffect playerExplode = {
			.poolId = "SMOKE_HEAVY_POOL",
			.originMin = {0,0},
			.originMax = {0,0},
			.forceMin = 5,
			.forceMax = 15,
			.lifetimeMin = 1.2F,
			.lifetimeMax = 1.5F,
			.alphaFade = true,
			.angleMin = 0,
			.angleMax = 360,
			.particleSizeMin = 5.1,
			.particleSizeMax = 5.2,
			.colorRangeBegin = {180,0,0,255},
			.colorRangeEnd = {255,30,76,255},
			.particleSpawnCountMin = 20,
			.particleSpawnCountMax = 40
	};	
	
	static const ParticleEffect gibs = {
			.poolId = "GIBS_POOL",
			.originMin = {0,0},
			.originMax = {0,0},
			.forceMin = 1,
			.forceMax = 5,
			.lifetimeMin = 5,
			.lifetimeMax = 5,
			.alphaFade = true,
			.angleMin = 0,
			.angleMax = 360,
			.particleSizeMin = 3.1,
			.particleSizeMax = 9.2,
			.colorRangeBegin = {221,209,70,255},
			.colorRangeEnd = {240,219,80,255},
			.particleSpawnCountMin = 3,
			.particleSpawnCountMax = 7
	};
}
