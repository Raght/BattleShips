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

Mesh::Mesh(const std::vector<olc::vf2d>& mesh_points, const olc::Pixel& mesh_color)
	: points(mesh_points), color(mesh_color)
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



MissileMesh::MissileMesh()
{
}

MissileMesh::MissileMesh(const std::vector<olc::vf2d>& mesh_points, const PositionedVector& tip_of_the_weapon_origin, const olc::Pixel& mesh_color)
	: Mesh(mesh_points, mesh_color), tip_of_the_weapon_origin(tip_of_the_weapon_origin)
{

}

void MissileMesh::Scale(float scale_factor)
{
	Mesh::Scale(scale_factor, tip_of_the_weapon_origin.position);
}

MissileMesh MissileMesh::GetScaledMesh(float scale_factor)
{
	MissileMesh scaled_mesh = *this;
	scaled_mesh.Scale(scale_factor);
	return scaled_mesh;
}

void MissileMesh::Translate(olc::vf2d move)
{
	Mesh::Translate(move);
	tip_of_the_weapon_origin.position += move;
}

MissileMesh MissileMesh::ReturnTranslatedMesh(olc::vf2d move)
{
	MissileMesh translated_mesh = *this;
	translated_mesh.Translate(move);
	return translated_mesh;
}

void MissileMesh::Rotate(olc::vf2d rotation_origin, float degrees)
{
	Mesh::Rotate(rotation_origin, degrees);
	tip_of_the_weapon_origin.position = RotateVectorAroundPoint(tip_of_the_weapon_origin.position, rotation_origin, Radians(degrees));
	tip_of_the_weapon_origin.direction = RotateVector(tip_of_the_weapon_origin.direction, Radians(degrees));
}

MissileMesh MissileMesh::ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees)
{
	MissileMesh rotated_mesh = *this;
	rotated_mesh.Rotate(rotation_origin, degrees);
	return rotated_mesh;
}



WeaponMesh::WeaponMesh()
{

}

WeaponMesh::WeaponMesh(const std::vector<olc::vf2d>& mesh_points,
	const std::vector<PositionedVector>& missile_origins,
	const PositionedVector& weapon_to_ship_origin,
	const olc::Pixel& mesh_color)
	: Mesh(mesh_points, mesh_color), missile_origins(missile_origins), weapon_to_ship_origin(weapon_to_ship_origin)
{
	
}

void WeaponMesh::Scale(float scale_factor)
{
	Mesh::Scale(scale_factor, weapon_to_ship_origin.position);
}

WeaponMesh WeaponMesh::GetScaledMesh(float scale_factor)
{
	WeaponMesh scaled_mesh = *this;
	scaled_mesh.Scale(scale_factor);
	return scaled_mesh;
}

void WeaponMesh::Translate(olc::vf2d move)
{
	Mesh::Translate(move);
	for (PositionedVector& origin : missile_origins)
	{
		origin.position += move;
	}
	weapon_to_ship_origin.position += move;
}

WeaponMesh WeaponMesh::ReturnTranslatedMesh(olc::vf2d move)
{
	WeaponMesh translated_mesh = *this;
	translated_mesh.Translate(move);
	return translated_mesh;
}

void WeaponMesh::Rotate(olc::vf2d rotation_origin, float degrees)
{
	Mesh::Rotate(rotation_origin, degrees);
	for (PositionedVector& origin : missile_origins)
	{
		origin.position = RotateVectorAroundPoint(origin.position, rotation_origin, Radians(degrees));
		origin.direction = RotateVector(origin.direction, Radians(degrees));
	}
	weapon_to_ship_origin.position = RotateVectorAroundPoint(weapon_to_ship_origin.position, rotation_origin, Radians(degrees));
	weapon_to_ship_origin.direction = RotateVector(weapon_to_ship_origin.direction, Radians(degrees));
}

WeaponMesh WeaponMesh::ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees)
{
	WeaponMesh rotated_mesh = *this;
	rotated_mesh.Rotate(rotation_origin, degrees);
	return rotated_mesh;
}



HullMesh::HullMesh()
{

}

HullMesh::HullMesh(const std::vector<olc::vf2d>& mesh_points,
	const PositionedVector& ship_origin,
	const PositionedVector& weapon_to_ship_origin,
	const olc::Pixel& mesh_color)
	: Mesh(mesh_points, mesh_color), ship_origin(ship_origin), weapon_to_ship_origin(weapon_to_ship_origin)
{

}

void HullMesh::Scale(float scale_factor)
{
	Mesh::Scale(scale_factor, ship_origin.position);
	ScalePoint(weapon_to_ship_origin.position, scale_factor, ship_origin.position);
}

HullMesh HullMesh::GetScaledMesh(float scale_factor)
{
	HullMesh scaled_mesh = *this;
	scaled_mesh.Scale(scale_factor);
	return scaled_mesh;
}

void HullMesh::Translate(olc::vf2d move)
{
	Mesh::Translate(move);
	ship_origin.position += move;
	weapon_to_ship_origin.position += move;
}

HullMesh HullMesh::ReturnTranslatedMesh(olc::vf2d move)
{
	HullMesh translated_mesh = *this;
	translated_mesh.Translate(move);
	return translated_mesh;
}

void HullMesh::Rotate(olc::vf2d rotation_origin, float degrees)
{
	Mesh::Rotate(rotation_origin, degrees);
	ship_origin.position = RotateVectorAroundPoint(ship_origin.position, rotation_origin, Radians(degrees));
	weapon_to_ship_origin.position = RotateVectorAroundPoint(weapon_to_ship_origin.position, rotation_origin, Radians(degrees));
	ship_origin.direction = RotateVector(ship_origin.direction, Radians(degrees));
	weapon_to_ship_origin.direction = RotateVector(weapon_to_ship_origin.direction, Radians(degrees));
}

HullMesh HullMesh::ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees)
{
	HullMesh rotated_mesh = *this;
	rotated_mesh.Rotate(rotation_origin, degrees);
	return rotated_mesh;
}