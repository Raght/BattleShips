#include "Ship.h"


Ship::Ship(ShipPrototype ship_prototype, olc::vf2d initial_position, olc::vf2d initial_direction,
	const std::string& name, Team team, float initial_velocity)
{
	maxHealth = ship_prototype.health;
	health = maxHealth;
	maxVelocity = ship_prototype.maxVelocity;
	maxAcceleration = ship_prototype.acceleration;
	maxBoostAcceleration = ship_prototype.boost_acceleration;

	position = initial_position;
	direction = initial_direction;
	velocity = initial_velocity * direction;
	velocity_magnitude = initial_velocity;
	acceleration = 0 * direction;


	this->name = name;
	this->team = team;
}

void Ship::TurnLeft(float degrees)
{
	direction = Rotate(direction, Radians(degrees));
}

void Ship::TurnRight(float degrees)
{
	direction = Rotate(direction, Radians(-degrees));
}

void Ship::AccelerateForward()
{
	acceleration = maxAcceleration * direction;
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

void Ship::TryShoot()
{

}

void Ship::TakeDamage(float damage)
{
	health -= damage;
	if (Equal(health, 0) || health < 0)
	{
		m_IsDead = true;
	}
}

bool Ship::IsDead()
{
	return m_IsDead;
}