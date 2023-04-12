#pragma once
#include "MobyDick.h"

class MRContactFilter : public ContactFilter
{
public:
	MRContactFilter();
	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) final;

};

