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

	bool exploExist(string type)
	{
		return explosions_.find(type) != explosions_.end();
	}

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

	void addExplosionToCache(Explosion* exp)
	{
		string type = exp->particles_[0]->graphics->getType();
		if (exploExist(type))
			return;

		this->explosions_[type] = exp->clone();
	}

	Explosion* reuseExplosion(string type)
	{
		return explosions_.at(type)->clone();
	}
};

class ExplosionCacheProxy : public IExplosionFactory
{

};