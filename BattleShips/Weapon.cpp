#include "Weapon.h"



WeaponPrototype::WeaponPrototype() { }

WeaponPrototype::WeaponPrototype(const Mesh& _mesh,
	const MissilePrototype& _missilePrototype, const std::vector<GameObject>& firing_positions,
	int32_t _maxAmmo, int32_t _missilesPerShot, int32_t _ammoPerShot)
	: missilePrototype(_missilePrototype), maxAmmo(_maxAmmo), missilesPerShot(_missilesPerShot), ammoPerShot(_ammoPerShot)
{
	mesh = _mesh;
	childrenGameObjects = firing_positions;
}


Weapon::Weapon() { }

Weapon::Weapon(olc::vf2d position, olc::vf2d direction, const WeaponPrototype& weapon_prototype)
	: WeaponPrototype(weapon_prototype)
{
	ammo = weapon_prototype.maxAmmo;

	mesh.Move(position - mesh.weapon_to_ship_origin.position);
	mesh.Rotate(mesh.weapon_to_ship_origin.position, Degrees(AngleBetweenToRotateAntiClockwise(mesh.weapon_to_ship_origin.direction, direction)));

	random_firing_positions_distribution = std::uniform_int_distribution<int>(0, childrenGameObjects.size() - 1);
}


bool Weapon::TryShoot(std::vector<Missile>& missiles)
{
	missiles.clear();
	if (ammo <= 0)
		return false;

	std::unordered_set<int> firing_origin_indexes;
	
	for (int i = 0; i < missilesPerShot; i++)
	{
		int firing_origin_index;
		while (true)
		{
			firing_origin_index = random_firing_positions_distribution(rng);
			if (firing_origin_indexes.find(firing_origin_index) == firing_origin_indexes.end())
				break;
		}
		firing_origin_indexes.insert(firing_origin_index);

		GameObject firing_origin = childrenGameObjects[firing_origin_index];
		Missile missile = Missile(missilePrototype, firing_origin.position, firing_origin.direction);
		missiles.push_back(missile);
	}

	ammo = std::max(0, ammo - ammoPerShot);

	return true;
}

