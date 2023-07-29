#include "Mesh.h"



Polygon::Polygon()
{

}

Polygon::Polygon(const std::vector<olc::vf2d>& points)
	: points(points)
{

}

PositionedVector::PositionedVector()
	: position(0.0, 0.0), direction(1.0, 0.0)
{

}

PositionedVector::PositionedVector(olc::vf2d position, olc::vf2d direction)
	: position(position), direction(direction)
{

}



Mesh::Mesh()
{

}

Mesh::Mesh(olc::vf2d center, olc::vf2d rotation, const std::vector<olc::vf2d>& mesh_points, olc::Pixel mesh_color)
	: center(center), rotation(rotation), points(mesh_points), color(mesh_color)
{
	
}

void Mesh::PrintData()
{
	std::cout << "Points: \n";
	for (olc::vf2d& v : points)
	{
		std::cout << v.x << ' ' << v.y << '\n';
	}
	std::cout << "\nColor: \n";
	std::cout << '(' << (uint32_t)color.r << ", " << (uint32_t)color.g << ", " << (uint32_t)color.b << ")\n\n";
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
	for (olc::vf2d& point : points)
	{
		ScalePoint(point, scale_factor, center);
	}
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

void Mesh::Translate(olc::vf2d move)
{
	for (olc::vf2d& point : points)
	{
		point += move;
	}
}

Mesh Mesh::ReturnTranslatedMesh(olc::vf2d move)
{
	Mesh translated_mesh = *this;
	translated_mesh.Translate(move);
	return translated_mesh;
}


void Mesh::Rotate(olc::vf2d rotation_origin, float degrees)
{
	for (olc::vf2d& point : points)
	{
		point = RotateVectorAroundPoint(point, rotation_origin, Radians(degrees));
	}
}

Mesh Mesh::ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees)
{
	Mesh rotated_mesh = *this;
	rotated_mesh.Rotate(rotation_origin, degrees);
	return rotated_mesh;
}