#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Particle.cpp"

using namespace std;

class Explosion
{
public:
	string spread;
    vector<Particle*> particles_;
};

class IExplosionBuilder
{
public:
	virtual ~IExplosionBuilder() = default;

	virtual void withPosition() const = 0;
	virtual void withColor() const = 0;
	virtual void withLifetime() const = 0;
	virtual void withSpread() const = 0;
	virtual void withCount() const = 0;

	virtual void build() const = 0;
};

class ClassicExplosionBuilder : public IExplosionBuilder
{
private:
	Explosion* explosionObj;
	Particle pBlueprint;
	int count = 0;

public:
	ClassicExplosionBuilder()
	{
		this->Reset();
	}
	~ClassicExplosionBuilder()
	{
		delete explosionObj;
	}

	void Reset()
	{
		this->explosionObj = new Explosion();
	}

	void withPosition(Position p)
	{
		pBlueprint.position = p;
	}
		
	void withColor(string color)
	{
		pBlueprint.color = color;
	}

	void withLifetime(int lifetime)
	{
		pBlueprint.lifetime = lifetime;
	}

	void withSpread(string spread)
	{
		this->explosionObj->spread = spread;
	}

	void withCount(int count)
	{
		this->count = count;
	}

	virtual void build()
	{
		for (int i = 0; i < count; i++)
		{
		    explosionObj->particles_.push_back(pBlueprint.clone());
		}
	}

	Explosion* GetExplosion() {
		Explosion* epxlo = this->explosionObj;
		this->Reset();
		return epxlo;
	}
};