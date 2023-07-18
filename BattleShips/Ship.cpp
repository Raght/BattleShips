#include "Ship.h"



Ship::Ship(const HullPrototype& hull_prototype, const WeaponPrototype& weapon_prototype,
	olc::vf2d initial_position, olc::vf2d initial_direction,
	const std::string& name, Team team, float initial_velocity)
{
	position = initial_position;
	direction = initial_direction;
	velocity = initial_velocity * direction;
	acceleration = 0 * direction;

	hull = Hull(hull_prototype, position, direction);
	weapon = Weapon(weapon_prototype, position, direction);



	this->name = name;
	this->team = team;
}


void Ship::SetAcceleration(olc::vf2d new_acceleration)
{
	acceleration = new_acceleration;
	hull.acceleration = new_acceleration;
	weapon.acceleration = new_acceleration;
}


void Ship::Rotate(olc::vf2d point, float degrees)
{
	float radians = Radians(degrees);

	direction = RotateVector(direction, radians);
	hull.mesh.Rotate(position, radians);
	weapon.mesh.Rotate(position, radians);
}

void Ship::UpdatePosition(float fElapsedTime)
{
	olc::vf2d new_velocity = velocity + acceleration * fElapsedTime;
	//if (new_velocity.dot(velocity) < 0.0f)
	//{
	//	new_velocity = velocity;
	//}

	if (new_velocity.mag2() > hull.maxVelocity * hull.maxVelocity)
		new_velocity = new_velocity / new_velocity.mag() * hull.maxVelocity;

	velocity = new_velocity;
	position += velocity * fElapsedTime;
}




void Ship::TurnLeft(float degrees)
{
	Rotate(position, degrees);
}

void Ship::TurnRight(float degrees)
{
	Rotate(position, -degrees);
}

void Ship::AccelerateForward()
{
	olc::vf2d new_acceleration = maxAcceleration * direction;
	if (acceleration.mag2() > new_acceleration.mag2())
		return;
	SetAcceleration(new_acceleration);
}

void Ship::StopAccelerating()
{
	SetAcceleration(0 * direction);
}

void Ship::Brake()
{
	olc::vf2d new_acceleration = -maxAcceleration * direction;
	if (new_acceleration.dot(velocity) > 0.0f)
		StopAccelerating();
	else
		SetAcceleration(new_acceleration);
}

void Ship::TryShoot()
{
	this->TakeDamage(10);
}

void Ship::TakeDamage(float damage)
{
	hull.health -= damage;
	if (Equal(hull.health, 0) || hull.health < 0)
	{
		m_IsDead = true;
	}
}

void Ship::DealDamage(float damage, Ship& ship)
{
	ship.TakeDamage(damage);
}

bool Ship::IsDead()
{
	return m_IsDead;
}