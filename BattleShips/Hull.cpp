#include "Hull.h"



HullPrototype::HullPrototype()
{

}

HullPrototype::HullPrototype(float maxHealth, float maxVelocity, float maxAcceleration, const HullMesh& mesh)
	: maxHealth(maxHealth), maxVelocity(maxVelocity), maxAcceleration(maxAcceleration), mesh(mesh)
{

}


Hull::Hull()
{

}

Hull::Hull(const HullPrototype& hull_prototype, olc::vf2d position, olc::vf2d direction)
	: HullPrototype(hull_prototype)
{
	health = hull_prototype.maxHealth;

	mesh.Translate(position - mesh.ship_origin.position);
	mesh.Rotate(mesh.ship_origin.position, AngleBetweenToRotateAntiClockwise(mesh.ship_origin.direction, direction));
	
}

