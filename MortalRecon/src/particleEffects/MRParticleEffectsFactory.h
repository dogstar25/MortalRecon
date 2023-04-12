#pragma once
#include "MobyDick.h"

#include "GameParticleEffects.h"


class MRParticleEffectsFactory : public ParticleEffectsFactory{



public:

	virtual ParticleEffect create(std::string particleType) override;


private:




};
