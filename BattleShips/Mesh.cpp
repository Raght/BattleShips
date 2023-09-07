#include "Mesh.h"



Shape::Shape()
{

}

Shape::Shape(const std::vector<olc::vf2d>& _points, olc::Pixel _color, bool _is_convex, DrawingMode _drawing_mode)
	: points(_points), color(_color), isConvex(_is_convex), drawingMode(_drawing_mode)
{

}



Mesh::Mesh()
{
	//*this = MISSING_MESH;
}

Mesh::Mesh(olc::vf2d _center, olc::vf2d _direction, const std::vector<Shape>& _polygons,
	bool _all_polygons_set_convex, DrawingMode _all_polygons_force_drawing_mode)
	: center(_center), direction(_direction)
{
	m_AllPolygonsAreConvex = _all_polygons_set_convex;
	m_AllPolygonsForcedDrawingMode = _all_polygons_force_drawing_mode;
	polygons = _polygons;
	//for (Shape& polygon : polygons)
	//{
	//	polygon.isConvex = _all_polygons_set_convex;
	//	polygon.drawingMode = _all_polygons_force_drawing_mode;
	//}
}

void Mesh::ScalePoint(olc::vf2d& point, float scale_factor, olc::vf2d center)
{
	point = center + scale_factor * (point - center);
}

olc::vf2d Mesh::GetScaledPoint(olc::vf2d point, float scale_factor, olc::vf2d center)
{
	olc::vf2d scaled_point = point;
	ScalePoint(scaled_point, scale_factor, center);
	return scaled_point;
}

void Mesh::Scale(float scale_factor, olc::vf2d center)
{
	for (Shape& polygon : polygons)
	{
		for (olc::vf2d& point : polygon.points)
		{
			ScalePoint(point, scale_factor, center);
		}
	}
	ScalePoint(center, scale_factor, center);
}

Mesh Mesh::GetScaledMesh(float scale_factor, olc::vf2d center)
{
	Mesh scaled_mesh = *this;
	scaled_mesh.Scale(scale_factor, center);
	return scaled_mesh;
}

void Mesh::ScalePoint(olc::vf2d& point, float scale_factor)
{
	ScalePoint(point, scale_factor, center);
}

olc::vf2d Mesh::GetScaledPoint(olc::vf2d point, float scale_factor)
{
	return GetScaledPoint(point, scale_factor, center);
}

void Mesh::Scale(float scale_factor)
{
	Scale(scale_factor, center);
}

Mesh Mesh::GetScaledMesh(float scale_factor)
{
	return GetScaledMesh(scale_factor, center);
}

void Mesh::Move(olc::vf2d move)
{
	for (Shape& polygon : polygons)
	{
		for (olc::vf2d& point : polygon.points)
		{
			point += move;
		}
	}
	center += move;
}

Mesh Mesh::ReturnTranslatedMesh(olc::vf2d move)
{
	Mesh translated_mesh = *this;
	translated_mesh.Move(move);
	return translated_mesh;
}


void Mesh::Rotate(olc::vf2d rotation_origin, float degrees)
{
	for (Shape& polygon : polygons)
	{
		for (olc::vf2d& point : polygon.points)
		{
			point = RotatePointAroundOrigin(point, rotation_origin, Radians(degrees));
		}
	}

	center = RotatePointAroundOrigin(center, rotation_origin, Radians(degrees));
	direction = RotateVector(direction, Radians(degrees));
}

Mesh Mesh::ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees)
{
	Mesh rotated_mesh = *this;
	rotated_mesh.Rotate(rotation_origin, degrees);
	return rotated_mesh;
}

void Mesh::Rotate(float degrees)
{
	Rotate(center, degrees);
}

Mesh Mesh::ReturnRotatedMesh(float degrees)
{
	Mesh rotated_mesh = *this;
	rotated_mesh.Rotate(center, degrees);
	return rotated_mesh;
}

void Mesh::ChangeColor(olc::Pixel color, BlendMode blend_mode)
{
	for (Shape& polygon : polygons)
	{
		polygon.color = BlendColorsNoAlpha(polygon.color, color, blend_mode);
	}
}

bool Mesh::AllPolygonsAreConvex()
{
	return m_AllPolygonsAreConvex;
}

DrawingMode Mesh::AllPolygonsForcedDrawingMode()
{
	return m_AllPolygonsForcedDrawingMode;
}