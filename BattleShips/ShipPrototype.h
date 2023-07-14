#pragma once
#include "olcPixelGameEngine.h"


class ShipPrototype
{
public:
	ShipPrototype(float max_health, float max_velocity, float max_acceleration, float boost_max_acceleration);

	float health;
	float maxVelocity;
	float acceleration;
	float boost_acceleration;
};