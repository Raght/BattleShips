#pragma once
#include "olcPixelGameEngine.h"
#include <vector>


class Mesh
{
public:
	Mesh(const std::vector<olc::vf2d>& mesh_points, const olc::Pixel& mesh_color = olc::WHITE);
	std::vector<olc::vf2d> points;
	olc::Pixel color;

	void PrintData();
};


struct Origin
{
	Origin();
	Origin(olc::vf2d position, olc::vf2d direction);

	olc::vf2d position;
	olc::vf2d direction;
};


class WeaponMesh : public Mesh
{
public:
	WeaponMesh(const std::vector<olc::vf2d>& mesh_points,
		const std::vector<Origin>& missile_origins,
		const Origin& weapon_to_ship_origin,
		const olc::Pixel& mesh_color = olc::WHITE);

	std::vector<Origin> missile_origins;
	Origin weapon_to_ship_origin;

};