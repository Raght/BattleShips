#include "Weapon.h"



WeaponPrototype::WeaponPrototype()
{

}

WeaponPrototype::WeaponPrototype(int32_t maxAmmo, WeaponMesh mesh, MissilePrototype missilePrototype,
	int32_t missilesPerShot, int32_t ammoPerShot)
	: maxAmmo(maxAmmo), mesh(mesh), missilePrototype(missilePrototype), missilesPerShot(missilesPerShot), ammoPerShot(ammoPerShot)
{

}


Weapon::Weapon()
{

}

Weapon::Weapon(const WeaponPrototype& weapon_prototype, olc::vf2d position, olc::vf2d direction)
	: WeaponPrototype(weapon_prototype)
{
	ammo = weapon_prototype.maxAmmo;

	mesh.Translate(position - mesh.weapon_to_ship_origin.position);
	mesh.Rotate(mesh.weapon_to_ship_origin.position, Degrees(AngleBetweenToRotateAntiClockwise(mesh.weapon_to_ship_origin.direction, direction)));

	random_firing_positions_distribution = std::uniform_int_distribution<int>(0, mesh.missile_origins.size() - 1);
}

void Weapon::Move(olc::vf2d move)
{
	GameObject::Move(move);
	mesh.Translate(move);
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

		PositionedVector firing_origin = mesh.missile_origins[firing_origin_index];
		Missile missile = Missile(missilePrototype, firing_origin.position, firing_origin.direction);
		missiles.push_back(missile);
	}

	ammo = std::max(0, ammo - ammoPerShot);

	return true;
}

