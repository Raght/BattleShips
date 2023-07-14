#pragma once
#include "olcPixelGameEngine.h"
#include <vector>


struct Mesh
{
	std::vector<olc::vf2d> points;
	olc::Pixel color;
};