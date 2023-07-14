#pragma once
#include "olcPixelGameEngine.h"


enum class KeyState { PRESSED, HELD, RELEASED };
enum class Action { TURN_LEFT, TURN_RIGHT, MOVE_FORWARD, STOP, SHOOT, PICK_UP };

struct KeyStateAction
{
	KeyStateAction(olc::Key key, KeyState key_state_to_act, Action action)
	{
		this->key = key;
		keyStateToAct = key_state_to_act;
		this->action = action;
	}

	olc::Key key;
	KeyState keyStateToAct;
	Action action;
};

struct ControlScheme
{
	ControlScheme() {}
	ControlScheme(const std::vector<KeyStateAction>& key_state_actions, float turning_speed_degrees_per_second = 180)
	{
		keyStateActions = key_state_actions;
		turningSpeedDegreesPerSecond = turning_speed_degrees_per_second;
	}

	std::vector<KeyStateAction> keyStateActions;
	float turningSpeedDegreesPerSecond = 180;
};