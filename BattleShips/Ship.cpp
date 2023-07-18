#include "Ship.h"



ShipPrototype::ShipPrototype(float max_health, float max_velocity, float max_acceleration)
	: maxHealth(max_health), maxVelocity(max_velocity), maxAcceleration(max_acceleration)
{

}

ShipPrototype::ShipPrototype(const ShipPrototype& ship_prototype)
{
	*this = ship_prototype;
}



Ship::Ship(HullPrototype hull_prototype, WeaponPrototype weapon_prototype,
	olc::vf2d initial_position, olc::vf2d initial_direction,
	const std::string& name, Team team, float initial_velocity)
{
	hull = Hull(hull_prototype);
	weapon = Weapon(weapon_prototype);

	position = initial_position;
	direction = initial_direction;
	velocity = initial_velocity * direction;
	acceleration = 0 * direction;


	this->name = name;
	this->team = team;
}


void Ship::Rotate(olc::vf2d point, float degrees)
{
	float radians = Radians(degrees);

	weapon.mesh.Rotate(position, degrees);
	hull.mesh.Rotate();
	direction = RotateVector(direction, radians);
}

void Ship::UpdatePosition(float fElapsedTime)
{
	olc::vf2d new_velocity = velocity + acceleration * fElapsedTime;
	//if (new_velocity.dot(velocity) < 0.0f)
	//{
	//	new_velocity = velocity;
	//}

	if (new_velocity.mag2() > maxVelocity * maxVelocity)
		new_velocity = new_velocity / new_velocity.mag() * maxVelocity;

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
	acceleration = new_acceleration;
}

void Ship::StopAccelerating()
{
	acceleration = 0 * direction;
}

void Ship::Brake()
{
	olc::vf2d new_acceleration = -maxAcceleration * direction;
	if (new_acceleration.dot(velocity) > 0.0f)
		acceleration = 0 * direction;
	else
		acceleration = new_acceleration;
}

void Ship::TryShoot()
{
	this->TakeDamage(10);
}

void Ship::TakeDamage(float damage)
{
	health -= damage;
	if (Equal(health, 0) || health < 0)
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