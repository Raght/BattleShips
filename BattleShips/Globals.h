#pragma once
#include "ControlScheme.h"
#include "ShipPrototype.h"
#include "MissilePrototype.h"
#include "WeaponPrototype.h"
#include "Mesh.h"


inline ControlScheme control_scheme_player_first = ControlScheme({
	KeyStatesForAction({{olc::W, KeyState::HELD}}, Action::MOVE_FORWARD),
	KeyStatesForAction({{olc::W, KeyState::HELD}, {olc::SHIFT, KeyState::HELD}}, Action::BOOST_FORWARD),
	KeyStatesForAction({{olc::S, KeyState::HELD}}, Action::STOP),
	KeyStatesForAction({{olc::A, KeyState::HELD}}, Action::TURN_LEFT),
	KeyStatesForAction({{olc::D, KeyState::HELD}}, Action::TURN_RIGHT),
	KeyStatesForAction({{olc::SPACE, KeyState::PRESSED}}, Action::SHOOT),
});

inline ControlScheme control_scheme_player_second = ControlScheme({
	KeyStatesForAction({{olc::NP8, KeyState::HELD}}, Action::MOVE_FORWARD),
	KeyStatesForAction({{olc::NP8, KeyState::HELD}, {olc::UP, KeyState::HELD}}, Action::BOOST_FORWARD),
	KeyStatesForAction({{olc::NP5, KeyState::HELD}}, Action::STOP),
	KeyStatesForAction({{olc::NP4, KeyState::HELD}}, Action::TURN_LEFT),
	KeyStatesForAction({{olc::NP6, KeyState::HELD}}, Action::TURN_RIGHT),
	KeyStatesForAction({{olc::RETURN, KeyState::PRESSED}}, Action::SHOOT),
});


ShipPrototype assault = ShipPrototype(100, 100, 100);
ShipPrototype scout = ShipPrototype(50, 120, 200);
ShipPrototype heavy = ShipPrototype(200, 80, 60);

std::vector<ShipPrototype> ship_prototypes = { assault, scout, heavy };

Mesh quad;
quad.points = { {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0} };
quad.color = { 0, 255, 0 };
WeaponMesh weapon_mesh;
weapon_mesh.points = { {-0.5, 0.0}, {0.5, 0.0}, {0.5, 2.0}, {-0.5, 2.0} };
weapon_mesh.color = { 0, 255, 0 };
weapon_mesh.missile_origins = { {{0.0, 2.0}, {0.0, 1.0}} };
weapon_mesh.weapon_to_ship_origin = { {0.0, EPSILON}, {0.0, 1.0} };