#pragma once
#include "Missile.h"
#include "PhysicsObject.h"
#include "Mesh.h"
#include <random>


class WeaponPrototype
{
public:
	WeaponPrototype();

	int32_t maxAmmo;
	int32_t missiles_per_shot = 1;
	int32_t ammo_per_shot = missiles_per_shot;
	Mesh mesh;
	MissilePrototype missile_prototype;

};


class Weapon : public PhysicsObject, public WeaponPrototype
{
public:
	Weapon();

	olc::vf2d direction;

	int32_t ammo;


	bool TryShoot(std::vector<Missile>& missiles);

private:
	std::uniform_int_distribution<int> random_firing_positions_distribution;
};