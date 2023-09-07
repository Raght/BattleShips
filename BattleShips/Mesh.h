#pragma once
#include "olcPixelGameEngine.h"
#include "Math.h"
#include "Draw.h"
#include "Color.h"
#include <vector>



struct Shape
{
	Shape();
	Shape(const std::vector<olc::vf2d>& points, olc::Pixel color, bool is_convex = false, DrawingMode drawingMode = DrawingMode::OUTLINE);

	std::vector<olc::vf2d> points;
	olc::Pixel color;
	bool isConvex;
	DrawingMode drawingMode;
};

class Mesh
{
public:
	Mesh();
	Mesh(olc::vf2d center, olc::vf2d direction, const std::vector<Shape>& mesh_points,
		bool all_polygons_set_convex = false, DrawingMode all_polygons_force_drawing_mode = DrawingMode::UNDEFINED);
	
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

	void ChangeColor(olc::Pixel color, BlendMode blend_mode = BlendMode::REPAINT);

	olc::vf2d center;
	olc::vf2d direction;
	std::vector<Shape> polygons;

	bool AllPolygonsAreConvex();
	DrawingMode AllPolygonsForcedDrawingMode();

private:
	bool m_AllPolygonsAreConvex;
	DrawingMode m_AllPolygonsForcedDrawingMode;
};