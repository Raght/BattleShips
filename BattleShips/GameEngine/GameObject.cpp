#include "GameObject.h"



GameObject::GameObject(const GameObject& game_object, olc::vf2d position, olc::vf2d direction)
{
	*this = GameObject::Instantiate(game_object, position, direction);
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

GameObject::GameObject(olc::vf2d _position, olc::vf2d _direction, const Mesh& _mesh, const std::vector<GameObject*>& _children_gameobjects)
{
	childrenGameObjects = _children_gameobjects;
	//for (GameObject& pGameObject : childrenGameObjects)
	//{
	//	pGameObject.Move(position - _position);
	//	pGameObject.AlignDirection(_direction);
	//}

	position = _position;
	direction = _direction;

	mesh = _mesh;
	mesh.Move(position - mesh.center);
	mesh.Rotate(Degrees(AngleBetweenToRotateAntiClockwise(mesh.direction, direction)));
}

GameObject GameObject::Instantiate(GameObject prefab, olc::vf2d _position, olc::vf2d _direction)
{
	prefab.MoveTo(_position);
	prefab.AlignDirection(_direction);
	return prefab;
}

void GameObject::AttachTo(GameObject* game_object)
{
	game_object->childrenGameObjects.push_back(this);
}

void GameObject::Move(olc::vf2d move)
{
	position += move;
	mesh.Move(move);
	for (GameObject* pGameObject : childrenGameObjects)
	{
		pGameObject->Move(move);
	}
}

void GameObject::MoveTo(olc::vf2d _position)
{
	Move(_position - position);
}

void GameObject::Scale(olc::vf2d scale_origin, float new_scale)
{
	assert(scale != 0 && new_scale != 0);

	Move((new_scale - 1) * Scale() * (position - scale_origin));
	mesh.Scale(new_scale / Scale(), scale_origin);
	for (GameObject* pGameObject : childrenGameObjects)
	{
		pGameObject->Scale(position, new_scale);
	}
	scale = new_scale;
}

GameObject GameObject::GetScaledGameObject(olc::vf2d scale_origin, float new_scale)
{
	GameObject scaled_game_object = *this;
	scaled_game_object.Scale(scale_origin, new_scale);
	return scaled_game_object;
}

void GameObject::Scale(float new_scale)
{
	Scale(position, new_scale);
}

GameObject GameObject::GetScaledGameObject(float new_scale)
{
	GameObject scaled_game_object = *this;
	scaled_game_object.Scale(new_scale);
	return scaled_game_object;
}

void GameObject::Rotate(olc::vf2d rotation_origin, float degrees)
{
	position = RotatePointAroundOrigin(position, rotation_origin, Radians(degrees));
	mesh.Rotate(rotation_origin, degrees);
	direction = RotateVector(direction, Radians(degrees));
	for (GameObject* pGameObject : childrenGameObjects)
	{
		pGameObject->Rotate(rotation_origin, degrees);
	}
}

void GameObject::Rotate(float degrees)
{
	Rotate(position, degrees);
}

void GameObject::AlignDirection(olc::vf2d new_direction)
{
	float angle_to_rotate = Degrees(AngleBetweenToRotateAntiClockwise(direction, new_direction));
	Rotate(angle_to_rotate);
}

float GameObject::Scale()
{
	return scale;
}

bool GameObject::LifetimeExceeded() const
{
	return (lifetimeSeconds != INFINITE_LIFETIME) && lifetime > lifetimeSeconds;
}
