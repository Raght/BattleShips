#pragma once
#include <complex>
#include "olcPixelGameEngine.h"
#include "ShipPrototype.h"
#include "Team.h"
#include "GameObject.h"
#include "Math.h"


class Ship : public GameObject
{
public:
	Ship(ShipPrototype ship_prototype, olc::vf2d initial_position, olc::vf2d initial_direction,
		const std::string& name, Team team, float initial_velocity = 0);

	void TurnLeft(float degrees);
	void TurnRight(float degrees);
	void AccelerateForward();
	void StopAccelerating();
	void Brake();

	void UpdatePosition(float fElapsedTime);

	void TryShoot();

	void TakeDamage(float damage);
	bool IsDead();

	float health;
	float maxHealth;
	
	float velocity_magnitude;
	float acceleration_magnitude;

	float maxVelocity;
	float maxAcceleration;
	float maxBoostAcceleration;

	olc::vf2d direction;

	float maxSize;

	std::string name;
	Team team;

private:
	bool m_IsDead = false;
};