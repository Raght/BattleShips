#pragma once
#include "PhysicsObject.h"
#include "Mesh.h"


class HullPrototype : public GameObject
{
public:
	HullPrototype();
	HullPrototype(const Mesh& mesh, float maxHealth, float maxVelocity, float maxAcceleration);

	float maxHealth;
	float maxVelocity;
	float maxAcceleration;
};


class Hull : public HullPrototype
{
public:
	Hull();
	Hull(olc::vf2d position, olc::vf2d direction, const HullPrototype& hull_prototype);

	void Move(olc::vf2d move);

	float health;
};