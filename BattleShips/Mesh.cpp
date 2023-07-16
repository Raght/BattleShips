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


Origin::Origin()
	: position(0.0, 0.0), direction(1.0, 0.0)
{

}

Origin::Origin(olc::vf2d position, olc::vf2d direction)
	: position(position), direction(direction)
{

}


WeaponMesh::WeaponMesh(const std::vector<olc::vf2d>& mesh_points,
	const std::vector<Origin>& missile_origins,
	const Origin& weapon_to_ship_origin,
	const olc::Pixel& mesh_color = olc::WHITE)
	: Mesh(mesh_points, mesh_color), missile_origins(missile_origins), weapon_to_ship_origin(weapon_to_ship_origin)
{
	
}