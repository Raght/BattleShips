#pragma once
#include "Missile.h"
#include "PhysicsObject.h"
#include "Mesh.h"
#include "GlobalsMechanics.h"
#include <unordered_set>


class WeaponPrototype : public GameObject
{
public:
	WeaponPrototype();
	WeaponPrototype(const Mesh& mesh,
		const MissilePrototype& missilePrototype, const std::vector<GameObject>& firing_positions,
		int32_t maxAmmo, int32_t missilesPerShot = 1, int32_t ammoPerShot = 1);

	int32_t maxAmmo;
	int32_t missilesPerShot = 1;
	int32_t ammoPerShot = missilesPerShot;
	MissilePrototype missilePrototype;
};


class Weapon : public WeaponPrototype
{
public:
	Weapon();
	Weapon(olc::vf2d position, olc::vf2d direction, const WeaponPrototype& weapon_prototype);

	int32_t ammo;


	bool TryShoot(std::vector<Missile>& missiles);

private:
	std::uniform_int_distribution<int> random_firing_positions_distribution;
};