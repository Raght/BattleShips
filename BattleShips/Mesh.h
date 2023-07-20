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
	Mesh(const std::vector<olc::vf2d>& mesh_points, const olc::Pixel& mesh_color = olc::WHITE);

	void PrintData();

	void ScalePoint(olc::vf2d& point, float scale_factor, olc::vf2d center = { 0.0, 0.0 });
	olc::vf2d GetScaledPoint(olc::vf2d point, float scale_factor, olc::vf2d center = { 0.0, 0.0 });
	void Scale(float scale_factor, olc::vf2d center = { 0.0, 0.0 });
	Mesh GetScaledMesh(float scale_factor, olc::vf2d center = { 0.0, 0.0 });
	void Translate(olc::vf2d move);
	Mesh ReturnTranslatedMesh(olc::vf2d move);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	Mesh ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees);

	std::vector<olc::vf2d> points;
	olc::Pixel color;
};


class MissileMesh : public Mesh
{
public:
	MissileMesh();
	MissileMesh(const std::vector<olc::vf2d>& mesh_points,
		const PositionedVector& tip_of_the_weapon_origin,
		const olc::Pixel& mesh_color = olc::WHITE);

	void Scale(float scale_factor);
	MissileMesh GetScaledMesh(float scale_factor);
	void Translate(olc::vf2d move);
	MissileMesh ReturnTranslatedMesh(olc::vf2d move);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	MissileMesh ReturnRotatedMesh(olc::vf2d rotation_origin, float degrees);

	PositionedVector tip_of_the_weapon_origin;
};


class HullMesh : public Mesh
{
public:
	HullMesh();
	HullMesh(const std::vector<olc::vf2d>& mesh_points,
		const PositionedVector& ship_origin,
		const PositionedVector& weapon_to_ship_origin,
		const olc::Pixel& mesh_color);

	void Scale(float scale_factor);
	HullMesh GetScaledMesh(float scale_factor);
	void Translate(olc::vf2d move);
	HullMesh ReturnTranslatedMesh(olc::vf2d move);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	HullMesh ReturnRotatedMesh(olc::vf2d point, float degrees);

	PositionedVector ship_origin = PositionedVector({ 0, 0 }, { 1, 0 });
	PositionedVector weapon_to_ship_origin;
};


class WeaponMesh : public Mesh
{
public:
	WeaponMesh();
	WeaponMesh(const std::vector<olc::vf2d>& mesh_points,
		const std::vector<PositionedVector>& missile_origins,
		const PositionedVector& weapon_to_ship_origin,
		const olc::Pixel& mesh_color = olc::WHITE);

	void Scale(float scale_factor);
	WeaponMesh GetScaledMesh(float scale_factor);
	void Translate(olc::vf2d move);
	WeaponMesh ReturnTranslatedMesh(olc::vf2d move);
	void Rotate(olc::vf2d rotation_origin, float degrees);
	WeaponMesh ReturnRotatedMesh(olc::vf2d point, float degrees);

	std::vector<PositionedVector> missile_origins;
	PositionedVector weapon_to_ship_origin = PositionedVector({ 0, EPSILON }, { 1, 0 });
};