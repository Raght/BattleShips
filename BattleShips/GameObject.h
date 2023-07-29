#pragma once
#include "olcPixelGameEngine.h"
#include "Mesh.h"


class GameObject
{
public:
	GameObject();
	GameObject(olc::vf2d position);

	void Move(olc::vf2d move);

	olc::vf2d position;
	olc::vf2d rotation;
	float scale = 1.0f;

	Mesh mesh;
};