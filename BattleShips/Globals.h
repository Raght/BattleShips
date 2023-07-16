#pragma once
#include <random>
#include "ControlScheme.h"
#include "Ship.h"
#include "Missile.h"
#include "Weapon.h"
#include "Mesh.h"


inline std::random_device device;
inline std::default_random_engine rng(device());


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


Mesh quad(
	{ {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0} },
	{ 0, 255, 0 }
);
WeaponMesh weapon_assault_cannon_mesh(
	{ {-16.5, 0.0}, {16.5, 0.0}, {16.5, 33}, {-16.5, 33} },
	{ {{0.0, 2.0}, {0.0, 1.0}} },
	{ {0.0, EPSILON}, {0.0, 1.0} },
	{ 0, 255, 0 }
);