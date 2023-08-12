#pragma once
#include "GameObject.h"


class Hull : public GameObject
{
public:
	Hull();
	Hull(const Prefab& hull_prefab, float maxHealth, float maxVelocity, float maxAcceleration, olc::vf2d position = { 0.0, 0.0 }, olc::vf2d direction = { 0.0, 1.0 });

	float health;
	float maxHealth;
	float maxVelocity;
	float maxAcceleration;
};