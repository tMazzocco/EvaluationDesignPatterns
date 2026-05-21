#pragma once
#include "ParticleFlyweight.cpp"
#include <memory>


struct Position
{
protected:
	float x = 0;
	float y = 0;
	float taille = 0;
	float vitesse = 0;
	string color;

public:
	Position() { }

	Position(string color)
	{
		this->color = color;
	}
};

class IParticlePrototype
{
protected:
	IParticlePrototype() {}
	IParticlePrototype(shared_ptr<ParticleFlyweight> pf) {
		this->graphics = pf;
		this->position = Position();
	}

public:

	Position position;
	shared_ptr<ParticleFlyweight> graphics;

	virtual IParticlePrototype *clone() const = 0;
};

class Particle : public IParticlePrototype
{
private:

public:
	IParticlePrototype *clone() const override
	{
		return new Particle(*this);
	}
};