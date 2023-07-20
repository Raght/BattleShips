#include "Missile.h"


MissilePrototype::MissilePrototype()
{

}

MissilePrototype::MissilePrototype(float damage, float velocity, MissileMesh mesh, float acceleration)
	: damage(damage), velocityMagnitude(velocity), mesh(mesh), accelerationMagnitude(acceleration)
{

}

Missile::Missile()
{

}

Missile::Missile(MissilePrototype missile_prototype,
	olc::vf2d position, olc::vf2d direction,
	float lifetimeSeconds)
	: MissilePrototype(missile_prototype)
{
	this->position = position;
	this->velocity = velocityMagnitude * direction;
	this->acceleration = accelerationMagnitude * direction;

	mesh.Translate(position - mesh.tip_of_the_weapon_origin.position);
	mesh.Rotate(mesh.tip_of_the_weapon_origin.position, Degrees(AngleBetweenToRotateAntiClockwise(mesh.tip_of_the_weapon_origin.direction, direction)));

	this->lifetimeSeconds = lifetimeSeconds;
}

void Missile::UpdatePosition(float fElapsedTime)
{
	PhysicsObject::UpdatePosition(fElapsedTime);

	mesh.Translate(position - mesh.tip_of_the_weapon_origin.position);
}
