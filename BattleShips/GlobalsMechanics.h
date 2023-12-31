#pragma once
#include <random>





inline const olc::vf2d DIRECTION_RIGHT = { 1.0, 0.0 };
inline const olc::vf2d DIRECTION_UP = { 0.0, 1.0 };
inline const olc::vf2d DIRECTION_LEFT = { -1.0, 0.0 };
inline const olc::vf2d DIRECTION_DOWN = { 0.0, -1.0 };


inline const Mesh EMPTY_MESH = Mesh();
inline const Mesh MISSING_MESH = Mesh(
	{ 0.0, 0.0 }, { 1.0, 0.0 },
	{
		Shape({{0, 0}, {50, 0}, {50, 50}, {0, 50}}, olc::BLUE),
		Shape({{-50, -50}, {0, -50}, {0, 0}, {-50, 0}}, olc::BLUE),
		Shape({{-50, 0}, {0, 0}, {0, 50}, {-50, 50}}, olc::MAGENTA),
		Shape({{0, -50}, {50, -50}, {50, 0}, {0, 0}}, olc::MAGENTA),
	}
);
inline const Mesh DOT_MESH = Mesh(
	{ 0.0, 0.0 }, { 1.0, 0.0 },
	{
		Shape({{0.0, 0.0}}, olc::WHITE)
	}
);
inline const Mesh LINE_MESH = Mesh(
	{ 0.0, 0.0 }, { 1.0, 0.0 },
	{
		Shape({{0.0, 0.0}, {1.0, 0.0}}, olc::WHITE)
	}
);
inline const Mesh LINE_MESH_SIZE_100 = Mesh(
	{ 0.0, 0.0 }, { 1.0, 0.0 },
	{
		Shape({{0.0, 0.0}, {100.0, 0.0}}, olc::WHITE)
	}
);

inline const Mesh QUAD = Mesh(
	{ 0.0, 0.0 }, { 1.0, 0.0 },
	{
		Shape({{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0} }, olc::WHITE)
	}
);
inline const Mesh QUAD_SIZE_100 = Mesh(
	{ 0.0, 0.0 }, { 1.0, 0.0 },
	{
		Shape({{0.0, 0.0}, {0.0, 100.0}, {1.0, 100.0}, {100.0, 0.0} }, olc::WHITE)
	}
);

inline const GameObject NULL_GAMEOBJECT = GameObject();