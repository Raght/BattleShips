#pragma once
#include "WeaponPrototype.h"
#include "MissilePrototype.h"
#include "PhysicsObject.h"


class Weapon : public GameObject
{
public:
	int32_t ammo;
	int32_t maxAmmo;
	MissilePrototype missile_prototype;

	void TryShoot();
};