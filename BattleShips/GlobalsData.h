#pragma once
#include "olcPixelGameEngine.h"
#include <random>
#include "ControlScheme.h"
#include "Ship.h"
#include "Missile.h"
#include "Weapon.h"
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


inline Mesh quad(
	{ {0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0} },
	{ 0, 255, 0 }
);


inline float _scale_factor = 20.0f / 27 * 4 / 3;

inline HullMesh hull_assault_mesh = HullMesh(
	{ {-45, 0}, {45, 0}, {45, 30}, {-45, 30} },
	{ { 0, 15 }, {0, 1} },
	{ { 0, 0 }, {0, 1} },
	olc::GREEN
).GetScaledMesh(_scale_factor);

inline WeaponMesh weapon_assault_cannon_mesh = WeaponMesh(
	{ {-15, 0.0}, {15, 0.0}, {15, 60}, {-15, 60} },
	{ {{0.0, 60}, {0.0, 1.0}} },
	{ {0.0, EPSILON}, {0.0, 1.0} },
	olc::GREEN
).GetScaledMesh(_scale_factor);



inline HullPrototype assault(100, 100, 100, hull_assault_mesh);
inline HullPrototype scout(50, 120, 200, hull_assault_mesh);
inline HullPrototype heavy(200, 80, 60, hull_assault_mesh);

inline std::vector<HullPrototype> hull_prototypes = { assault, scout, heavy };

inline MissileMesh assault_missile_mesh = MissileMesh(
	{ {-5, 0.0}, {5, 0.0}, {5, 20}, {-5, 20} },
	{ {0.0, 20}, {0.0, 1.0} },
	olc::WHITE
).GetScaledMesh(_scale_factor);

inline MissilePrototype assault_missile(10, 200, assault_missile_mesh);

inline WeaponPrototype assault_cannon(50, weapon_assault_cannon_mesh, assault_missile);


