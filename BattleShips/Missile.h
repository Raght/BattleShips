#pragma once
#include "PhysicsObject.h"



class MissilePrototype
{

};



class Missile : public PhysicsObject, public MissilePrototype
{
public:
	float lifetime = 0.0f;


	//void Update(float fElapsedTime)
	//{
	//	vector<GameObject> collided_objects
	//}
};