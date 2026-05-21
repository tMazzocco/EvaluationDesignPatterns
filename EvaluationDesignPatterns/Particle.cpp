#pragma once
#include "ParticleFlyweight.cpp"
#include <memory>


struct Position
{
public:
	float x = 0;
	float y = 0;

	Position() { }
	Position(float x, float y) {
		this->x = x;
		this->y = y;
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

	float taille = 0;
	float vitesse = 0;
	string color;
	Position position;
	int lifetime = 1;
	shared_ptr<ParticleFlyweight> graphics;

	virtual IParticlePrototype* clone() const = 0;
};

class Particle : public IParticlePrototype
{
private:

public:
	Particle() {}
	Particle* clone() const override
	{
		return new Particle(*this);
	}
};