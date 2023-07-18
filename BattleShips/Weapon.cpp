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
{
	ammo = weapon_prototype.maxAmmo;

	mesh.Translate(position - mesh.weapon_to_ship_origin.position);
	mesh.Rotate(mesh.weapon_to_ship_origin.position, AngleBetweenToRotateAntiClockwise(mesh.weapon_to_ship_origin.direction, direction));
}


bool Weapon::TryShoot(std::vector<Missile>& missiles)
{
	missiles.clear();
	if (ammo <= 0)
		return false;

	std::unordered_set<int> 
	
	for (int i = 0; i < missilesPerShot; i++)
	{

		missiles.push_back(Missile(missilePrototype, );
	}

	ammo = std::max(0, ammo - ammoPerShot);

	return true;
}

