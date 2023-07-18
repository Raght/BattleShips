#include "GameObject.h"


GameObject::GameObject()
{

}

void GameObject::Move(olc::vf2d move)
{
	position += move;
}
