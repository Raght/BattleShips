#pragma once
#include "PhysicsObject.h"
#include "Mesh.h"



class MissilePrototype
{
public:
	MissilePrototype();
	MissilePrototype(float damage, float velocity, MissileMesh mesh, float acceleration = 0);

	float damage;
	float velocityMagnitude;
	MissileMesh mesh;
	float accelerationMagnitude = 0;
};



class Missile : public PhysicsObject, public MissilePrototype
{
public:
	Missile();
	Missile(MissilePrototype missile_prototype,
		olc::vf2d position, olc::vf2d direction,
		float lifetimeSeconds = 5.0f);

	void UpdatePosition(float fElapsedTime);

	float lifetimeSeconds;

	//void Update(float fElapsedTime)
	//{
	//	vector<GameObject> collided_objects
	//}
};