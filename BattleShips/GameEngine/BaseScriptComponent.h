#pragma once
#include "GameObject.h"


class BaseScriptComponent
{
public:
	GameObject* gameObjectAttachedTo = nullptr;

	virtual void OnStart() = 0;
	virtual void OnUpdate(float fElapsedTime) = 0;
	void CoreUpdate(float fElapsedTime);
};