#pragma once
#include "olcPixelGameEngine.h"
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


Mesh quad(
	{ {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0} },
	{ 0, 255, 0 }
);


HullMesh hull_assault_mesh(
	{ {-50, 0}, {50, 0}, {50, 33}, {-50, 33} },
	{ { 0, 16.5 }, {0, 1} },
	{ { 0, 33 }, {0, 1} },
	olc::GREEN
);

WeaponMesh weapon_assault_cannon_mesh(
	{ {-16.5, 0.0}, {16.5, 0.0}, {16.5, 66}, {-16.5, 66} },
	{ {{0.0, 2.0}, {0.0, 1.0}} },
	{ {0.0, EPSILON}, {0.0, 1.0} },
	olc::GREEN
);



HullPrototype assault = HullPrototype(100, 100, 100, hull_assault_mesh);
HullPrototype scout = HullPrototype(50, 120, 200, hull_assault_mesh);
HullPrototype heavy = HullPrototype(200, 80, 60, hull_assault_mesh);

std::vector<HullPrototype> hull_prototypes = { assault, scout, heavy };



