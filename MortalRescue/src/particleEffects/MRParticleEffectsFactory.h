#pragma once

#include "GameParticleEffects.h"
#include "particleEffects/ParticleEffectsFactory.h"

#include <memory>
#include <optional>


class MRParticleEffectsFactory : public ParticleEffectsFactory{



public:

	virtual ParticleEffect create(std::string particleType) override;


private:




};
