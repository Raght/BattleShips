#pragma once
#include "GameObject.h"


class PhysicsObject : public GameObject
{
public:
	PhysicsObject();

	olc::vf2d velocity;
	olc::vf2d acceleration;

	void SetAcceleration(olc::vf2d new_acceleration);

	void UpdatePosition(float fElapsedTime);
};