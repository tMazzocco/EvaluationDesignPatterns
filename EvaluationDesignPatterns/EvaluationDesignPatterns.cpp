#include <iostream>
#include <memory>
#include "FlyweightFactory.cpp"
#include "ExplosionBuilder.cpp"
#include "ExplosionCacheProxy.cpp"

#include "ExplosionFactory.cpp"


using namespace std;

FactorySingleton* FactorySingleton::ffInstance = nullptr;
ExplosionCache* ExplosionCache::instance = nullptr;

mutex FactorySingleton::mutex_ffInstance;

int main()
{
    BurnningExplosionCacheProxy burnningExplosionFactory;
    ElecExplosionCacheProxy eExFacto;


    cout << "--- Creating Explosion 1 (wood) ---\n";
    Explosion* explosion1 = burnningExplosionFactory.createExplosion(Position(50, 30));
    cout << "Explosion 1 created with " << explosion1->particles_.size() << " particles.\n";

    cout << "\n--- Creating Explosion 2 (wood1) ---\n";
    Explosion* explosion2 = burnningExplosionFactory.createExplosion(Position(20,10));
    cout << "Explosion 2 created with " << explosion2->particles_.size() << " particles.\n";

    cout << "\n--- Creating Explosion 3 (electric) ---\n";
    Explosion* explosion3 = eExFacto.createExplosion(Position(20, 10));
    cout << "Explosion 3created with " << explosion3->particles_.size() << " particles.\n";


    delete explosion1;
    delete explosion2;
    delete explosion3;

    return 0;
}
