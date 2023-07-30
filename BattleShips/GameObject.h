#pragma once
#include "olcPixelGameEngine.h"
#include "Math.h"
#include "Mesh.h"
#include <cassert>


inline const GameObject NULL_GAMEOBJECT = GameObject();


class GameObject
{
public:
	GameObject();
	GameObject(olc::vf2d position);
	GameObject(olc::vf2d position, olc::vf2d direction);
	GameObject(olc::vf2d position, olc::vf2d direction, const Mesh& mesh);

	void Move(olc::vf2d move);
	void Scale(olc::vf2d scale_origin, float new_scale);
	void Scale(float new_scale);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	void Rotate(float degrees);
	void AlignDirection(olc::vf2d new_direction);

	float Scale();

	olc::vf2d position = { 0, 0 };
	olc::vf2d direction = { 1, 0 };

	Mesh mesh;

	std::vector<GameObject> childrenGameObjects;

private:
	float scale = 1.0f;
};