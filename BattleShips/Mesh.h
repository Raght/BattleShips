#pragma once
#include "olcPixelGameEngine.h"
#include "Math.h"
#include <vector>


struct Polygon
{
	Polygon();
	Polygon(const std::vector<olc::vf2d>& points);

	std::vector<olc::vf2d> points;
};

struct PositionedVector
{
	PositionedVector();
	PositionedVector(olc::vf2d position, olc::vf2d direction);

	olc::vf2d position;
	olc::vf2d direction;
};


class Mesh
{
public:
	Mesh();
	Mesh(olc::vf2d center, olc::vf2d rotation, const std::vector<olc::vf2d>& mesh_points, olc::Pixel mesh_color);

	void PrintData();

	
	void ScalePoint(olc::vf2d& point, float scale_factor, olc::vf2d center);
	olc::vf2d GetScaledPoint(olc::vf2d point, float scale_factor, olc::vf2d center);
	void Scale(float scale_factor, olc::vf2d center);
	Mesh GetScaledMesh(float scale_factor, olc::vf2d center);

	void ScalePoint(olc::vf2d& point, float scale_factor);
	olc::vf2d GetScaledPoint(olc::vf2d point, float scale_factor);
	void Scale(float scale_factor);
	Mesh GetScaledMesh(float scale_factor);

	void Translate(olc::vf2d move);
	Mesh ReturnTranslatedMesh(olc::vf2d move);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	Mesh ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees);

	olc::vf2d center;
	olc::vf2d rotation;
	std::vector<olc::vf2d> points;
	olc::Pixel color;
};