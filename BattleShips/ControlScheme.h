#pragma once
#include "olcPixelGameEngine.h"


enum class KeyState { PRESSED, HELD, RELEASED };
enum class Action { TURN_LEFT, TURN_RIGHT, MOVE_FORWARD, BOOST_FORWARD, STOP, SHOOT, PICK_UP };

struct KeyStatePair
{
	olc::Key key;
	KeyState state;
};

struct KeyStatesForAction
{
	KeyStatesForAction(std::vector<KeyStatePair> key_states_to_act, Action action)
	{
		keyStatesToAct = key_states_to_act;
		this->action = action;
	}

	std::vector<KeyStatePair> keyStatesToAct;
	Action action;
};

struct ControlScheme
{
	ControlScheme() {}
	ControlScheme(const std::vector<KeyStatesForAction>& key_state_actions, float turning_speed_degrees_per_second = 180)
	{
		keyStateActions = key_state_actions;
		turningSpeedDegreesPerSecond = turning_speed_degrees_per_second;
	}

	std::vector<KeyStatesForAction> keyStateActions;
	float turningSpeedDegreesPerSecond = 180;
};