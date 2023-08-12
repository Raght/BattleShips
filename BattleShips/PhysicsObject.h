#pragma once
#include "GameObject.h"


class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	PhysicsObject(olc::vf2d position, olc::vf2d direction, olc::vf2d velocity, olc::vf2d acceleration);
	PhysicsObject(olc::vf2d position, olc::vf2d direction, olc::vf2d velocity, olc::vf2d acceleration, const Mesh& mesh);
	PhysicsObject(olc::vf2d position, olc::vf2d direction, olc::vf2d velocity, olc::vf2d acceleration, const Mesh& mesh, const std::vector<GameObject>& children_game_objects);

	olc::vf2d velocity = { 0.0f, 0.0f };
	olc::vf2d acceleration = { 0.0f, 0.0f };

	void SetAcceleration(olc::vf2d new_acceleration);
	void UpdatePosition(float elapsed_time);
};