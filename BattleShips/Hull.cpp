#include "Hull.h"


Hull::Hull(const HullPrototype& hull_prototype, olc::vf2d position, olc::vf2d direction)
	: HullPrototype(hull_prototype)
{
	health = hull_prototype.maxHealth;

	mesh.Translate(position - mesh.ship_origin.position);
	mesh.Rotate(mesh.ship_origin.position, AngleBetweenToRotateAntiClockwise(mesh.ship_origin.direction, direction));
	
}
