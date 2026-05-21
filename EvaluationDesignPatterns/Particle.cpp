#pragma once
#include "ParticleFlyweight.cpp"
#include <memory>


struct Position
{
public:
	float x;
	float y;
};

class Particle
{
private:

public:

	Position position;
	shared_ptr<ParticleFlyweight> graphics;
};