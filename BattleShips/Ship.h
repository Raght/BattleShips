#pragma once
#include <complex>
#include <vector>
#include "olcPixelGameEngine.h"
#include "Team.h"
#include "PhysicsObject.h"
#include "Hull.h"
#include "Weapon.h"
#include "Math.h"



class Ship : public PhysicsObject
{
public:
	Ship();
	Ship(const Hull& hull, const Weapon& weapon,
		olc::vf2d initial_position, olc::vf2d initial_direction,
		const std::string& name, Team team, olc::vf2d initial_velocity = {0.0f, 0.0f});

	void SetAcceleration(olc::vf2d new_acceleration);
	void Move(olc::vf2d move);
	void MoveTo(olc::vf2d new_position);
	void SetPosition(olc::vf2d new_position);
	void Rotate(olc::vf2d point, float degrees);
	void Rotate(float degrees);
	void AlignDirection(olc::vf2d new_direction);

	void UpdatePosition(float fElapsedTime);

	void TurnLeft(float degrees);
	void TurnRight(float degrees);
	void AccelerateForward();
	void StopAccelerating();
	void Brake();

	void TryShoot(std::vector<Missile>& missiles);

	void TakeDamage(float damage);
	void DealDamage(float damage, Ship& ship);
	bool IsDead();

	Hull hull;
	Weapon weapon;

	olc::vi2d sizeBoundingBox;

	std::string name;
	Team team;

private:
	bool m_IsDead = false;
};