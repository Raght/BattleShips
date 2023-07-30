#include "Hull.h"



HullPrototype::HullPrototype()
{

}

HullPrototype::HullPrototype(const Mesh& mesh, float maxHealth, float maxVelocity, float maxAcceleration)
	: mesh(mesh), maxHealth(maxHealth), maxVelocity(maxVelocity), maxAcceleration(maxAcceleration)
{

}


Hull::Hull()
{

}

Hull::Hull(olc::vf2d position, olc::vf2d direction, const HullPrototype& hull_prototype)
	: HullPrototype(hull_prototype), GameObject(position)
{
	health = hull_prototype.maxHealth;

	
	mesh.Move(position - mesh.ship_origin.position);
	mesh.Rotate(mesh.ship_origin.position, Degrees(AngleBetweenToRotateAntiClockwise(mesh.ship_origin.direction, direction)));
}

void Hull::Move(olc::vf2d move)
{
	GameObject::Move(move);
	mesh.Move(move);
}

