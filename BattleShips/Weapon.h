#pragma once
#include "Missile.h"
#include "PhysicsObject.h"
#include "Mesh.h"
#include "Globals.h"
#include <random>


class WeaponPrototype
{
public:
	WeaponPrototype();

	int32_t maxAmmo;
	int32_t missilesPerShot = 1;
	int32_t ammoPerShot = missilesPerShot;
	WeaponMesh mesh;
	MissilePrototype missilePrototype;

};


class Weapon : public PhysicsObject, public WeaponPrototype
{
public:
	Weapon(const WeaponPrototype& weapon_prototype, olc::vf2d position, olc::vf2d direction);


	int32_t ammo;


	bool TryShoot(std::vector<Missile>& missiles);

private:
	std::uniform_int_distribution<int> random_firing_positions_distribution;
};