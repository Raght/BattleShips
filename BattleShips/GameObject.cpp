#include "GameObject.h"


GameObject::GameObject()
{

}

GameObject::GameObject(olc::vf2d position)
	: position(position)
{
}

void GameObject::Move(olc::vf2d move)
{
	position += move;
}
