#pragma once
#include "PhysicsObject.h"
#include "Mesh.h"



class Missile : public PhysicsObject
{
public:
	Missile();
	Missile(const Mesh& missile_mesh,
		float damage, float velocity, 
		float lifetime_seconds = 10.0f, 
		olc::vf2d position = { 0.0f, 0.0f }, olc::vf2d direction = { 0.0f, 1.0f },
		float acceleration = 0.0f);

	Missile(const Missile& missile, olc::vf2d position, olc::vf2d direction);

	float damage;
	float velocityMagnitude;
	float accelerationMagnitude = 0;
};