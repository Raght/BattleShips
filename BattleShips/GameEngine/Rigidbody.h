#pragma once
#include "GameObject.h"
#include "BaseScriptComponent.h"


class Rigidbody : public BaseScriptComponent
{
public:
	Rigidbody(GameObject* game_object, olc::vf2d velocity, olc::vf2d acceleration);

	olc::vf2d velocity = { 0.0f, 0.0f };
	olc::vf2d acceleration = { 0.0f, 0.0f };

	void OnUpdate(float fElapsedTime) override;
};