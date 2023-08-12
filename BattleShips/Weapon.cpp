#include "Weapon.h"



Weapon::Weapon() { }

Weapon::Weapon(const Prefab& _weapon_prefab, const Missile& _missile,
	int32_t _max_ammo, int32_t _missiles_per_shot, int32_t _ammo_per_shot,
	olc::vf2d _position, olc::vf2d _direction)
	: GameObject(_weapon_prefab, _position, _direction),
	missile(_missile), ammo(_max_ammo), maxAmmo(_max_ammo), missilesPerShot(_missiles_per_shot), ammoPerShot(_ammo_per_shot)
{
	m_randomFiringPositionsDistribution = std::uniform_int_distribution<int>(0, childrenGameObjects.size() - 1ull);
}


bool Weapon::TryShoot(std::vector<Missile>& missiles)
{
	if (ammo <= 0)
		return false;

	std::unordered_set<int> firing_origin_indexes;
	
	for (int i = 0; i < missilesPerShot; i++)
	{
		int firing_origin_index;
		while (true)
		{
			firing_origin_index = m_randomFiringPositionsDistribution(rng);
			if (firing_origin_indexes.find(firing_origin_index) == firing_origin_indexes.end())
				break;
		}
		firing_origin_indexes.insert(firing_origin_index);

		GameObject& firing_origin = childrenGameObjects[firing_origin_index];
		Missile fired_missile = Missile(missile, firing_origin.position, firing_origin.direction);
		missiles.push_back(fired_missile);
	}

	ammo = std::max(0, ammo - ammoPerShot);

	return true;
}

