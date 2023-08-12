#include "PhysicsObject.h"



PhysicsObject::PhysicsObject()
{

}

PhysicsObject::PhysicsObject(olc::vf2d _position, olc::vf2d _direction, olc::vf2d _velocity, olc::vf2d _acceleration)
	: GameObject(_position, _direction)
{
	velocity = _velocity;
	acceleration = _acceleration;
}

PhysicsObject::PhysicsObject(olc::vf2d _position, olc::vf2d _direction, olc::vf2d _velocity, olc::vf2d _acceleration, const Mesh& _mesh)
	: GameObject(_position, _direction, _mesh)
{
	velocity = _velocity;
	acceleration = _acceleration;
}

PhysicsObject::PhysicsObject(olc::vf2d _position, olc::vf2d _direction, olc::vf2d _velocity, olc::vf2d _acceleration, const Mesh& _mesh, const std::vector<GameObject>& _children_game_objects)
	: GameObject(_position, _direction, _mesh, _children_game_objects)
{
	velocity = _velocity;
	acceleration = _acceleration;
}

void PhysicsObject::SetAcceleration(olc::vf2d new_acceleration)
{
	acceleration = new_acceleration;
}

void PhysicsObject::UpdatePosition(float elapsed_time)
{
	velocity += elapsed_time * acceleration;
	olc::vf2d new_position = position + elapsed_time * velocity;
	GameObject::MoveTo(new_position);
}