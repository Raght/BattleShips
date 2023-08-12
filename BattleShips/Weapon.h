#pragma once
#include "Missile.h"
#include "PhysicsObject.h"
#include "Mesh.h"
#include "GlobalsMechanics.h"
#include <unordered_set>



class Weapon : public GameObject
{
public:
	Weapon();
	Weapon(const Prefab& weapon_prefab, const Missile& missile,
		int32_t max_ammo, int32_t missiles_per_shot = 1, int32_t ammo_per_shot = 1,
		olc::vf2d position = { 0, 0 }, olc::vf2d direction = { 0.0, 1.0 });

	int32_t ammo;
	int32_t maxAmmo;
	int32_t missilesPerShot = 1;
	int32_t ammoPerShot = missilesPerShot;
	Missile missile;

	bool TryShoot(Team team, std::vector<Missile>& missiles);

private:
	std::uniform_int_distribution<int> m_randomFiringPositionsDistribution;
};