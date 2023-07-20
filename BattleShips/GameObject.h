#pragma once
#include "olcPixelGameEngine.h"


class GameObject
{
public:
	GameObject();
	GameObject(olc::vf2d position);

	void Move(olc::vf2d move);

	olc::vf2d position;
};