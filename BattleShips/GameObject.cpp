#include "GameObject.h"


GameObject::GameObject()
{

}

GameObject::GameObject(olc::vf2d _position)
	: GameObject()
{
	position = _position;
}

GameObject::GameObject(olc::vf2d _position, olc::vf2d _direction)
	: GameObject(_position)
{
	direction = _direction;
}

GameObject::GameObject(olc::vf2d _position, olc::vf2d _direction, const Mesh& _mesh)
	: GameObject(_position, _direction)
{
	mesh = _mesh;
	mesh.Move(position - mesh.center);
	mesh.Rotate(Degrees(AngleBetweenToRotateAntiClockwise(mesh.direction, direction)));
}

void GameObject::Move(olc::vf2d move)
{
	position += move;
	mesh.Move(move);
	for (GameObject pGameObject : childrenGameObjects)
	{
		pGameObject.Move(move);
	}
}

void GameObject::Scale(olc::vf2d scale_origin, float new_scale)
{
	assert(scale != 0 && new_scale != 0);
	mesh.Scale(new_scale / scale, scale_origin);
	scale = new_scale;
	for (GameObject pGameObject : childrenGameObjects)
	{
		pGameObject.Move((new_scale - 1) * pGameObject.Scale() * (pGameObject.position - scale_origin));
		pGameObject.Scale(position, pGameObject.Scale() * new_scale);
	}
}

void GameObject::Scale(float new_scale)
{
	Scale(position, new_scale);
}

void GameObject::Rotate(olc::vf2d rotation_origin, float degrees)
{
	mesh.Rotate(rotation_origin, degrees);
	direction = RotateVector(direction, Radians(degrees));
	for (GameObject pGameObject : childrenGameObjects)
	{
		pGameObject.Rotate(rotation_origin, degrees);
	}
}

void GameObject::Rotate(float degrees)
{
	Rotate(position, degrees);
}

void GameObject::AlignDirection(olc::vf2d new_direction)
{
	float angle_to_rotate = AngleBetweenToRotateAntiClockwise(direction, new_direction);
	mesh.Rotate(position, Degrees(angle_to_rotate));
	direction = new_direction;
	for (GameObject pGameObject : childrenGameObjects)
	{
		pGameObject.Rotate(position, angle_to_rotate);
	}
}

float GameObject::Scale()
{
	return scale;
}
