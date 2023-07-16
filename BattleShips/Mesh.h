#pragma once
#include "olcPixelGameEngine.h"
#include "Math.h"
#include <vector>


class Mesh
{
public:
	Mesh(const std::vector<olc::vf2d>& mesh_points, const olc::Pixel& mesh_color = olc::WHITE);

	void PrintData();

	void Translate(olc::vf2d move);
	Mesh ReturnTranslatedMesh(olc::vf2d move);
	void Rotate(olc::vf2d anchor_point, float degrees);
	Mesh ReturnRotatedMesh(olc::vf2d point, float degrees);

	std::vector<olc::vf2d> points;
	olc::Pixel color;
};


struct PositionedVector
{
	PositionedVector();
	PositionedVector(olc::vf2d position, olc::vf2d direction);

	olc::vf2d position;
	olc::vf2d direction;
};


class HullMesh : public Mesh
{
	HullMesh(const std::vector<olc::vf2d>& mesh_points,
		const PositionedVector& ship_origin,
		const PositionedVector& weapon_to_ship_origin,
		const olc::Pixel& mesh_color);

	void Translate(olc::vf2d move);
	Mesh ReturnTranslatedMesh(olc::vf2d move);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	Mesh ReturnRotatedMesh(olc::vf2d point, float degrees);

	PositionedVector ship_origin;
	PositionedVector weapon_to_ship_origin;
};


class WeaponMesh : public Mesh
{
public:
	WeaponMesh(const std::vector<olc::vf2d>& mesh_points,
		const std::vector<PositionedVector>& missile_origins,
		const PositionedVector& weapon_to_ship_origin,
		const olc::Pixel& mesh_color = olc::WHITE);

	void Translate(olc::vf2d move);
	Mesh ReturnTranslatedMesh(olc::vf2d move);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	Mesh ReturnRotatedMesh(olc::vf2d point, float degrees);

	std::vector<PositionedVector> missile_origins;
	PositionedVector weapon_to_ship_origin;
};