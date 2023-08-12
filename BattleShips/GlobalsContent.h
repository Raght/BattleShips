#pragma once
#include "olcPixelGameEngine.h"
#include <random>
#include "GlobalsMechanics.h"
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



// MESHES

inline float _scale_factor = 20.0f / 27 * 4 / 3;

// Hulls

inline Mesh hull_assault_mesh = Mesh(
	{ 0, 15 }, DIRECTION_UP,
	{
		Shape({{-45, 0}, {45, 0}, {45, 30}, {-45, 30} }, olc::GREEN)
	}
);

inline GameObject hull_assault_gameobject = GameObject(
	{ 0.0, 0.0 }, DIRECTION_UP,
	hull_assault_mesh,
	{
		GameObject({0.0, 15}, DIRECTION_UP)
	}
).GetScaledGameObject(_scale_factor);


// Missiles 

inline Mesh assault_missile_mesh = Mesh(
	{ 0.0, 20 }, { 0.0, 1.0 },
	{
		Shape({ {-5, 0.0}, {5, 0.0}, {5, 20}, {-5, 20} }, olc::WHITE)
	}
).GetScaledMesh(_scale_factor);


// Weapons

inline Mesh weapon_assault_cannon_mesh = Mesh(
	{0, 30}, DIRECTION_UP,
	{
		Shape({ {-15, 0.0}, {15, 0.0}, {15, 60}, {-15, 60} }, olc::GREEN)
	}
);

inline GameObject weapon_assault_cannon_gameobject = GameObject(
	{ 0, 0 }, DIRECTION_UP,
	weapon_assault_cannon_mesh,
	{
		GameObject({0.0, 30}, DIRECTION_UP)
	}
).GetScaledGameObject(_scale_factor);




// Prefabs

inline Hull hull_assault(hull_assault_gameobject, 100, 100, 100);
inline Hull hull_scout(hull_assault_gameobject, 50, 120, 200);
inline Hull hull_heavy(hull_assault_gameobject, 200, 80, 60);

inline std::vector<Hull> available_hulls = { hull_assault, hull_scout, hull_heavy };


inline Missile assault_missile(assault_missile_mesh, 10, 200);


inline Weapon assault_cannon(weapon_assault_cannon_gameobject, assault_missile, 50);

inline std::vector<Weapon> available_weapons = { assault_cannon };
