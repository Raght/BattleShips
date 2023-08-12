#include "Hull.h"



Hull::Hull()
{

}

Hull::Hull(const Prefab& _hull_prefab,
	float _maxHealth, float _maxVelocity, float _maxAcceleration,
	olc::vf2d _position, olc::vf2d _direction)
	: GameObject(_hull_prefab, _position, _direction),
	health(_maxHealth), maxHealth(_maxHealth), maxVelocity(_maxVelocity), maxAcceleration(_maxAcceleration)
{
	
}