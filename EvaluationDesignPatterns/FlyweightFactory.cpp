#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include <iostream>

#include "ParticleFlyweight.cpp"

using namespace std;


class IFlyweightFactory
{
private:
	virtual string GetKey(const IParticleFlyweight& pf) const = 0;

public:
	//virtual ParticleFlyweight createFlyweight() const = 0;
};


class FlyweightFactory : public IFlyweightFactory
{
private:
	unordered_map<string, ParticleFlyweight> flyweights_;

	string GetKey(const IParticleFlyweight& pf) const
	{
		return pf.getType();	
	}

public:

	FlyweightFactory(initializer_list<IParticleFlyweight> particle_flyweigth_state)
	{
	}

	FlyweightFactory() {}



	ParticleFlyweight getParticleFlyweight(ParticleFlyweight &pf)
	{
		if (this->flyweights_.find(pf.getType()) == this->flyweights_.end())
		{
			cout << "FlyweightFactory: Can't find a ParticleFlyweight, creating new one.\n";
			this->flyweights_.insert(std::make_pair(pf.getType(), ParticleFlyweight(pf)));
		}
		else
		{
			std::cout << "FlyweightFactory: Reusing existing ParticleFlyweight.\n";
		}
		return this->flyweights_.at(pf.getType());
	}
};

class FactorySingleton
{
private:
	static FactorySingleton* ffInstance;
	static mutex mutex_ffInstance;
	unique_ptr<FlyweightFactory> flyweightFactory;

	FactorySingleton() : flyweightFactory(make_unique<FlyweightFactory>()) {}

	~FactorySingleton() = default;


public:

	static FactorySingleton* getInstance()
	{
		lock_guard<mutex> lock(mutex_ffInstance);
		if (ffInstance == nullptr)
		{
			ffInstance = new FactorySingleton();
		}
		return ffInstance;
	};

	ParticleFlyweight getParticleFlyweight(ParticleFlyweight& pf)
	{
		return flyweightFactory->getParticleFlyweight(pf);
	}
};