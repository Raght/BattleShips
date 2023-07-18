#include "Weapon.h"


Weapon::Weapon(const WeaponPrototype& weapon_prototype, olc::vf2d position, olc::vf2d direction)
{

}


bool Weapon::TryShoot(std::vector<Missile>& missiles)
{
	missiles.clear();
	if (ammo <= 0)
		return false;

	
	for (int i = 0; i < missilesPerShot; i++)
	{

		missiles.push_back(Missile(missilePrototype, );
	}

	ammo = std::max(0, ammo - ammoPerShot);

	if (missiles.size())
		return true;
	return false;
}