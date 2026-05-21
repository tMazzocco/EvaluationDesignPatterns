#include <iostream>
#include <memory>
#include <unordered_map>
#include <mutex>

#include "FlyweightFactory.cpp"
#include "ExplosionBuilder.cpp"

#include "ExplosionFactory.cpp"


using namespace std;

class ExplosionCache
{
private:
	mutex mutex_explosionsCache;
	static ExplosionCache* instance;
	unordered_map<string, Explosion*> explosions_;

	ExplosionCache() {}


public:
	static ExplosionCache* getInstance()
	{
		static mutex static_mutex;
		lock_guard<mutex> lock(static_mutex);
		if (instance == nullptr)
		{
			instance = new ExplosionCache();
		}
		
		return instance;
	}

	bool exploExist(string type)
	{
		cout << "Checking if explo exist...\n";
		return explosions_.find(type) != explosions_.end();
	}

	void addExplosionToCache(Explosion* exp)
	{
		cout << "Adding explo to cache: " << exp->particles_[0]->graphics->getType() << "\n";
		string type = exp->particles_[0]->graphics->getType();
		if (exploExist(type))
			return;

		this->explosions_[type] = exp->clone();
	}

	Explosion* reuseExplosion(string type)
	{
		cout << "Reusing explosion: " << type << "\n";
		return explosions_.at(type)->clone();
	}
};

class ElecExplosionCacheProxy : public IExplosionFactory
{
private:
	string key = "electFly";
public:
	Explosion* createExplosion(Position p)
	{
		ExplosionCache* cache = ExplosionCache::getInstance();
		if (cache->exploExist(key))
		{
			return cache->reuseExplosion(key);
		}

		ElecExplosionFactory eExFacto;
		Explosion* explo = eExFacto.createExplosion(p);
		cache->addExplosionToCache(explo);
		return explo;
	}
};


class BurnningExplosionCacheProxy : public IExplosionFactory
{
private:
	string key = "burningFly";

public:
	Explosion* createExplosion(Position p)
	{
		ExplosionCache* cache = ExplosionCache::getInstance();
		if (cache->exploExist(key))
		{
			return cache->reuseExplosion(key);
		}

		BurningExplosionFactory factory;
		Explosion* explo = factory.createExplosion(p);
		cache->addExplosionToCache(explo);
		return explo;
	}
};