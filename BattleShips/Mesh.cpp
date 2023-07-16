#include "Mesh.h"


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


PositionedVector::PositionedVector()
	: position(0.0, 0.0), direction(1.0, 0.0)
{

}

PositionedVector::PositionedVector(olc::vf2d position, olc::vf2d direction)
	: position(position), direction(direction)
{

}



ShipMesh::ShipMesh(const std::vector<olc::vf2d>& mesh_points,
	const PositionedVector& ship_origin,
	const PositionedVector& weapon_to_ship_origin,
	const olc::Pixel& mesh_color)
	: Mesh(mesh_points, mesh_color), ship_origin(ship_origin), weapon_to_ship_origin(weapon_to_ship_origin)
{

}

void ShipMesh::Translate(olc::vf2d move)
{
	Mesh::Translate(move);
	ship_origin.position += move;
	weapon_to_ship_origin.position += move;
}

Mesh ShipMesh::ReturnTranslatedMesh(olc::vf2d move)
{
	ShipMesh translated_mesh = *this;
	translated_mesh.Translate(move);
	return translated_mesh;
}

void ShipMesh::Rotate(olc::vf2d rotation_origin, float degrees)
{
	Mesh::Rotate(rotation_origin, degrees);
	ship_origin.position = RotateVectorAroundPoint(ship_origin.position, rotation_origin, Radians(degrees));
	weapon_to_ship_origin.position = RotateVectorAroundPoint(weapon_to_ship_origin.position, rotation_origin, Radians(degrees));
	ship_origin.direction = RotateVector(ship_origin.direction, Radians(degrees));
	weapon_to_ship_origin.direction = RotateVector(weapon_to_ship_origin.direction, Radians(degrees));
}

Mesh ShipMesh::ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees)
{
	ShipMesh rotated_mesh = *this;
	rotated_mesh.Rotate(rotation_origin, degrees);
	return rotated_mesh;
}



WeaponMesh::WeaponMesh(const std::vector<olc::vf2d>& mesh_points,
	const std::vector<PositionedVector>& missile_origins,
	const PositionedVector& weapon_to_ship_origin,
	const olc::Pixel& mesh_color)
	: Mesh(mesh_points, mesh_color), missile_origins(missile_origins), weapon_to_ship_origin(weapon_to_ship_origin)
{
	
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

Mesh WeaponMesh::ReturnTranslatedMesh(olc::vf2d move)
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

Mesh WeaponMesh::ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees)
{
	WeaponMesh rotated_mesh = *this;
	rotated_mesh.Rotate(rotation_origin, degrees);
	return rotated_mesh;
}
