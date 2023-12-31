#include "Rigidbody.h"



Rigidbody::Rigidbody(GameObject* game_object, olc::vf2d _initial_velocity, olc::vf2d _constant_acceleration)
{
	gameObjectAttachedTo = game_object;
	velocity = _initial_velocity;
	acceleration = _constant_acceleration;
}


void Rigidbody::OnUpdate(float elapsed_time)
{
	olc::vf2d new_velocity = velocity + elapsed_time * acceleration;
	olc::vf2d new_position = gameObjectAttachedTo->position + elapsed_time * (velocity + new_velocity) / 2;
	velocity = new_velocity;
}