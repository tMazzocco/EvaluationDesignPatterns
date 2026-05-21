#pragma once

#include "FlyweightFactory.cpp"
#include "ExplosionBuilder.cpp"
#include "Particle.cpp"

using namespace std;

struct ExplosionConfig
{
    int count = 10;
    string spread = "wide";
    Position position;
    string color;
    int lifetime = 3;
    string particleType = "fire";
};

class IExplosionFactory
{
public:
    virtual Explosion* createExplosion(Position p) = 0;
};

class BurningExplosionFactory : public IExplosionFactory
{
private:
    void setUpFlyweight(Explosion* explo, string type)
    {
        ParticleFlyweight pf(type);
        shared_ptr<ParticleFlyweight> sharedPtr = FactorySingleton::getInstance()->getParticleFlyweight(pf);

        for (Particle* p : explo->particles_)
        {
            p->graphics = sharedPtr;
        }
    }

public:

    Explosion* createExplosion(Position p) override
    {
        ClassicExplosionBuilder builder = ClassicExplosionBuilder();
        builder.withColor("red");
        builder.withCount(10);
        builder.withLifetime(20);
        builder.withPosition(p);
        builder.withSpread("far");
        builder.build();
        Explosion* explo = builder.GetExplosion();
        setUpFlyweight(explo, "burningFly");
        return explo;
    }
};

class ElecExplosionFactory : public IExplosionFactory
{
private:
    void setUpFlyweight(Explosion* explo, string type)
    {
        ParticleFlyweight pf(type);
        // Récupère directement le shared_ptr stocké dans la map => même adresse
        shared_ptr<ParticleFlyweight> sharedPtr = FactorySingleton::getInstance()->getParticleFlyweight(pf);

        for (Particle* p : explo->particles_)
        {
            p->graphics = sharedPtr;
        }
    }

public:

    Explosion* createExplosion(Position p) override
    {
        ClassicExplosionBuilder builder = ClassicExplosionBuilder();
        builder.withColor("red");
        builder.withCount(50);
        builder.withLifetime(2);
        builder.withPosition(p);
        builder.withSpread("far");
        builder.build();
        Explosion* explo = builder.GetExplosion();
        setUpFlyweight(explo, "electFly");
        return explo;
    }
};