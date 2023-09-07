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
	KeyStatesForAction({{olc::ENTER, KeyState::PRESSED}}, Action::SHOOT),
});



// MESHES

inline float _scale_factor = 0.85f;

// Hulls

inline Mesh hull_assault_mesh = Mesh(
	{ 0, 16 }, DIRECTION_UP,
	{
		Shape({{-50, 0}, {50, 0}, {50, 33}, {-50, 33} }, olc::LIGHT_GREY, true, DrawingMode::FILL),
		Shape({ {-14, -2}, {14, -2}, {14, 55}, {-14, 55} }, olc::WHITE, true, DrawingMode::FILL),
	}
);

inline GameObject hull_assault_gameobject = GameObject(
	{ 0.0, 0.0 }, DIRECTION_UP,
	hull_assault_mesh,
	{
		GameObject({0.0, 14}, DIRECTION_UP)
	}
).GetScaledGameObject(_scale_factor);


// Missiles 

inline Mesh assault_missile_mesh = Mesh(
	{ 0.0, 20 }, { 0.0, 1.0 },
	{
		Shape({ {-5, 0.0}, {5, 0.0}, {5, 20}, {-5, 20} }, olc::WHITE, true, DrawingMode::FILL)
	}
);

inline Mesh smg_missile_mesh = Mesh(
	{ 0.0, 12 }, { 0.0, 1.0 },
	{
		Shape({ {-2, 0.0}, {2, 0.0}, {2, 12}, {-2, 12} }, olc::WHITE, true, DrawingMode::FILL)
	}
);

inline Mesh laser_missile_mesh = Mesh(
	{ 0.0, 20 }, { 0.0, 1.0 },
	{
		Shape({ {-3, 0.0}, {3, 0.0}, {3, 20}, {-3, 20} }, olc::WHITE, true, DrawingMode::FILL)
	}
);



// Weapons

inline Mesh weapon_assault_cannon_mesh = Mesh(
	{0, 33}, DIRECTION_UP,
	{
		//Shape({ {-16, 0.0}, {16, 0.0}, {16, 67}, {-16, 67} }, olc::WHITE, true, DrawingMode::FILL)
		Shape({ {-40, 0.0}, {-28, 0.0}, {-28, 50}, {-40, 50} }, olc::WHITE, true, DrawingMode::FILL),
		Shape({ {40, 0.0}, {28, 0.0}, {28, 50}, {40, 50} }, olc::WHITE, true, DrawingMode::FILL),
	}
);

inline GameObject weapon_assault_cannon_gameobject = GameObject(
	{ 0, 0 }, DIRECTION_UP,
	weapon_assault_cannon_mesh,
	{
		//GameObject({0.0, 33.5}, DIRECTION_UP)
		GameObject({-34, 50 - 33}, DIRECTION_UP),
		GameObject({34, 50 - 33}, DIRECTION_UP),
	}
).GetScaledGameObject(_scale_factor);


inline Mesh weapon_smg_cannon_mesh = Mesh(
	{ 0, 33 }, DIRECTION_UP,
	{
		//Shape({ {-24, 0.0}, {-20, 0.0}, {-20, 50}, {-24, 50} }, olc::WHITE, true, DrawingMode::FILL),
		//Shape({ {24, 0.0},  {20, 0.0},  {20, 50},  {24, 50} },  olc::WHITE, true, DrawingMode::FILL),
		//Shape({ {-34, 0.0}, {-30, 0.0}, {-30, 50}, {-34, 50} }, olc::WHITE, true, DrawingMode::FILL),
		//Shape({ {34, 0.0},  {30, 0.0},  {30, 50},  {34, 50} },  olc::WHITE, true, DrawingMode::FILL)
		Shape({ {-26, 0.0}, {-22, 0.0}, {-22, 50}, {-26, 50} }, olc::WHITE, true, DrawingMode::FILL),
		Shape({ {26, 0.0},  {22, 0.0},  {22, 50},  {26, 50} },  olc::WHITE, true, DrawingMode::FILL),
		Shape({ {-40, 0.0}, {-36, 0.0}, {-36, 46}, {-40, 46} }, olc::WHITE, true, DrawingMode::FILL),
		Shape({ {40, 0.0},  {36, 0.0},  {36, 46},  {40, 46} },  olc::WHITE, true, DrawingMode::FILL),
	}
);

inline GameObject weapon_smg_cannon_gameobject = GameObject(
	{ 0, 0 }, DIRECTION_UP,
	weapon_smg_cannon_mesh,
	{
		//GameObject({-22, 50 - 33}, DIRECTION_UP),
		//GameObject({22,  50 - 33}, DIRECTION_UP),
		//GameObject({-32, 50 - 33}, DIRECTION_UP),
		//GameObject({32,  50 - 33}, DIRECTION_UP)
		GameObject({-24, 50 - 33}, DIRECTION_UP),
		GameObject({24,  50 - 33}, DIRECTION_UP),
		GameObject({-38, 46 - 33}, DIRECTION_UP),
		GameObject({38,  46 - 33}, DIRECTION_UP),
	}
).GetScaledGameObject(_scale_factor);


inline Mesh weapon_laser_cannon_mesh = Mesh(
	{ 0, 33 }, DIRECTION_UP,
	{
		Shape({ {-40, 0.0}, {-34, 0.0}, {-34, 50}, {-40, 50} }, olc::WHITE, true, DrawingMode::FILL),
		Shape({ {40, 0.0}, {34, 0.0}, {34, 50}, {40, 50} }, olc::WHITE, true, DrawingMode::FILL),
	}
);

inline GameObject weapon_laser_cannon_gameobject = GameObject(
	{ 0, 0 }, DIRECTION_UP,
	weapon_laser_cannon_mesh,
	{
		GameObject({-37, 50 - 33}, DIRECTION_UP),
		GameObject({37, 50 - 33}, DIRECTION_UP),
	}
).GetScaledGameObject(_scale_factor);


// Prefabs

inline Hull hull_assault(hull_assault_gameobject, 100, 100, 100);
inline Hull hull_scout(hull_assault_gameobject, 50, 120, 200);
inline Hull hull_heavy(hull_assault_gameobject, 200, 80, 60);

inline std::vector<Hull> available_hulls = { hull_assault, hull_scout, hull_heavy };


inline Missile assault_missile(assault_missile_mesh, 10, 300);
inline Missile smg_missile(smg_missile_mesh, 5, 400);
inline Missile laser_missile(laser_missile_mesh, 7.5, 500);


inline Weapon assault_cannon(weapon_assault_cannon_gameobject, assault_missile, 50);
inline Weapon smg_cannon(weapon_smg_cannon_gameobject, smg_missile, 200);
inline Weapon laser_cannon(weapon_laser_cannon_gameobject, laser_missile, 100);

inline std::vector<Weapon> available_weapons = { assault_cannon, smg_cannon, laser_cannon };
