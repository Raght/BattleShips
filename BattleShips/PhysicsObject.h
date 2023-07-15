#pragma once
#include "GameObject.h"


class PhysicsObject : public GameObject
{
public:
	olc::vf2d velocity;
	olc::vf2d acceleration;
};