#pragma once
#include "PhysicsObject.h"
#include "Mesh.h"


class HullPrototype
{
public:
	HullPrototype();
	HullPrototype(float maxHealth, float maxVelocity, float maxAcceleration, const HullMesh& mesh);

	float maxHealth;
	float maxVelocity;
	float maxAcceleration;
	HullMesh mesh;
};


class Hull : public PhysicsObject, public HullPrototype
{
public:
	Hull();
	Hull(const HullPrototype& hull_prototype, olc::vf2d position, olc::vf2d direction);

	float health;
};