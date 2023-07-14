#pragma once
#include "Ship.h"
#include "ControlScheme.h"


class Player
{
public:
	Player(ControlScheme control_scheme, Ship* controlled_ship)
	{
		this->control_scheme = control_scheme;
		this->controlled_ship = controlled_ship;
	}

	ControlScheme control_scheme;
	Ship* controlled_ship;
};