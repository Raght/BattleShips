#pragma once
#include "PhysicsObject.h"
#include "Mesh.h"


class HullPrototype
{
	float health;
	float maxHealth;
	float maxVelocity;
	float maxAcceleration;
	HullMesh mesh;
};


class Hull : public PhysicsObject, public HullPrototype
{

};