#pragma once
#include <vector>
#include "olcPixelGameEngine.h"



struct Shape
{
	Shape();
	Shape(const std::vector<olc::vf2d>& points, olc::Pixel color);

	std::vector<olc::vf2d> points;
	olc::Pixel color;
};