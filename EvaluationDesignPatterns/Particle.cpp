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

class IParticle {
public:
	virtual IParticle* rendering() = 0;
	virtual ~IParticle() = default;

	virtual string getParticleColor() const = 0;
	virtual void setParticleColor(string color) = 0;
};

class IParticlePrototype : public IParticle
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

	string getParticleColor() const override
	{
		return this->color;
	}

	void setParticleColor(string color) override
	{
		this->color = color;
	}

	virtual IParticlePrototype* clone() const = 0;
};


class Particle : public IParticlePrototype
{
public:
	Particle() {}

	Particle(shared_ptr<ParticleFlyweight> pf) : IParticlePrototype(pf) {}

	Particle* clone() const override
	{
		return new Particle(*this);
	}

	Particle* rendering() override
	{
		return this;
	}
};