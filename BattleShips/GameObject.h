#pragma once
#include "olcPixelGameEngine.h"
#include "Math.h"
#include "Mesh.h"
#include <cassert>







class GameObject
{
public:
	GameObject();
	GameObject(const GameObject& game_object, olc::vf2d position, olc::vf2d direction);
	GameObject(olc::vf2d position);
	GameObject(olc::vf2d position, olc::vf2d direction);
	GameObject(olc::vf2d position, olc::vf2d direction, const Mesh& mesh);
	GameObject(olc::vf2d position, olc::vf2d direction, const Mesh& mesh, const std::vector<GameObject>& children_gameobjects);

	static GameObject Instantiate(GameObject prefab, olc::vf2d position, olc::vf2d direction);

	void Move(olc::vf2d move);
	void MoveTo(olc::vf2d position);
	void Scale(olc::vf2d scale_origin, float new_scale);
	GameObject GetScaledGameObject(olc::vf2d scale_origin, float new_scale);
	void Scale(float new_scale);
	GameObject GetScaledGameObject(float new_scale);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	void Rotate(float degrees);
	void AlignDirection(olc::vf2d new_direction);

	float Scale();


	bool LifetimeExceeded() const;

	olc::vf2d position = { 0, 0 };
	olc::vf2d direction = { 1, 0 };

	float lifetime = 0.0f;
	float lifetimeSeconds = -1.0f;

	Mesh mesh;

	std::vector<GameObject> childrenGameObjects;
	//std::vector<int> childrenGameObjects;

private:
	float scale = 1.0f;
};


typedef GameObject Prefab;