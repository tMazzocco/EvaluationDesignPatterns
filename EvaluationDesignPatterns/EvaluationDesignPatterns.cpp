#include <iostream>
#include <memory>
#include "FlyweightFactory.cpp"

using namespace std;

FactorySingleton* FactorySingleton::ffInstance = nullptr;
mutex FactorySingleton::mutex_ffInstance;

int main()
{
    cout << "Getting our instance throught the singleton :\n";
    FactorySingleton* factory = FactorySingleton::getInstance();

    cout << "Creating 2 Flyweight with identical types";
    ParticleFlyweight p1("burningFly", "shaderB", "small", "wood");
    ParticleFlyweight p2("metal");
    ParticleFlyweight p3("metal");
}
