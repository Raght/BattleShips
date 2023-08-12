#pragma once
#include "olcPixelGameEngine.h"
#include "Math.h"
#include <vector>



struct Shape
{
	Shape();
	Shape(const std::vector<olc::vf2d>& points, olc::Pixel color);

	std::vector<olc::vf2d> points;
	olc::Pixel color;
};

class Mesh
{
public:
	Mesh();
	Mesh(olc::vf2d center, olc::vf2d direction, const std::vector<Shape>& mesh_points);
	
	void ScalePoint(olc::vf2d& point, float scale_factor, olc::vf2d center);
	olc::vf2d GetScaledPoint(olc::vf2d point, float scale_factor, olc::vf2d center);
	void Scale(float scale_factor, olc::vf2d center);
	Mesh GetScaledMesh(float scale_factor, olc::vf2d center);

	void ScalePoint(olc::vf2d& point, float scale_factor);
	olc::vf2d GetScaledPoint(olc::vf2d point, float scale_factor);
	void Scale(float scale_factor);
	Mesh GetScaledMesh(float scale_factor);

	void Move(olc::vf2d move);
	Mesh ReturnTranslatedMesh(olc::vf2d move);

	void Rotate(olc::vf2d rotation_origin, float degrees);
	Mesh ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees);

	void Rotate(float degrees);
	Mesh ReturnRotatedMesh(float degrees);

	olc::vf2d center;
	olc::vf2d direction;
	std::vector<Shape> polygons;
};