#include "Missile.h"



Missile::Missile()
{

}

Missile::Missile(const Mesh& _missile_mesh,
	float _damage, float _velocity,
	float _lifetime_seconds,
	olc::vf2d _position, olc::vf2d _direction,
	float _acceleration)
	: PhysicsObject(_position, _direction, { 0, 0 }, { 0, 1.0 }, _missile_mesh),
	damage(_damage), velocityMagnitude(_velocity), accelerationMagnitude(_acceleration)
{
	velocity = _velocity * direction;
	acceleration = _acceleration * direction;

	lifetimeSeconds = _lifetime_seconds;
}

// TODO: does it call the GameObject constructor?
Missile::Missile(const Missile& _missile, olc::vf2d _position, olc::vf2d _direction)
	: Missile(_missile)
{
	MoveTo(_position);
	AlignDirection(_direction);
	velocity = _missile.velocityMagnitude * direction;
	acceleration = _missile.accelerationMagnitude * direction;
}
