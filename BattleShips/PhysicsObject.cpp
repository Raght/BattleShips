#include "PhysicsObject.h"



PhysicsObject::PhysicsObject()
{

}

void PhysicsObject::SetAcceleration(olc::vf2d new_acceleration)
{
	acceleration = new_acceleration;
}

void PhysicsObject::UpdatePosition(float fElapsedTime)
{
	velocity += fElapsedTime * acceleration;
	position += fElapsedTime * velocity;
}