#pragma once
#include "olcPixelGameEngine.h"


class GameObject
{
public:
	GameObject();

	void Move(olc::vf2d move);

	olc::vf2d position;
};