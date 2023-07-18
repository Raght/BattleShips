#pragma once
#include <complex>
#include "olcPixelGameEngine.h"
#include "Team.h"
#include "PhysicsObject.h"
#include "Hull.h"
#include "Weapon.h"
#include "Math.h"



class Ship : public PhysicsObject
{
public:
	Ship(const HullPrototype& hull_prototype, const WeaponPrototype& weapon_prototype,
		olc::vf2d initial_position, olc::vf2d initial_direction,
		const std::string& name, Team team, float initial_velocity = 0);

	void SetAcceleration(olc::vf2d new_acceleration);
	void Rotate(olc::vf2d point, float degrees);
	void UpdatePosition(float fElapsedTime);

	void TurnLeft(float degrees);
	void TurnRight(float degrees);
	void AccelerateForward();
	void StopAccelerating();
	void Brake();

	void TryShoot();

	void TakeDamage(float damage);
	void DealDamage(float damage, Ship& ship);
	bool IsDead();


	float maxHealth;
	float maxVelocity;
	float maxAcceleration;

	Hull hull;
	Weapon weapon;

	olc::vf2d direction;

	olc::vi2d sizeBoundingBox;


	std::string name;
	Team team;

private:
	bool m_IsDead = false;
};