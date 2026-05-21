#pragma once
#include <string>

using namespace std;

class IParticleFlyweight
{
protected:
	const string texture = "rougth";
	const string shader = "shaderA";
	const string physicalParametters = "non-newtonian";
	const string type;

	virtual ~IParticleFlyweight() = default;

public:
	IParticleFlyweight(
		const string texture,
		const string shader,
		const string physicalParametters,
		const string type)
	    : 
		texture(texture),
		shader(shader),
		physicalParametters(physicalParametters),
		type(type) { }

	IParticleFlyweight(const string type) : type(type) { }

	string getType() const
	{
		return this->type;
	}
};

class ParticleFlyweight : public IParticleFlyweight
{
public:
	ParticleFlyweight(const string type) : IParticleFlyweight(type) {}
	
	ParticleFlyweight(
		const string texture,
		const string shader,
		const string physicalParametters,
		const string type)
		: IParticleFlyweight(texture, shader, physicalParametters, type) {}
};