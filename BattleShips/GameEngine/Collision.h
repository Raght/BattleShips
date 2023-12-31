#pragma once
#include "olcPixelGameEngine.h"
#include "Mesh.h"


struct Segment
{
	olc::vf2d p1, p2;
};

bool SegmentVsSegment(Segment segment1, Segment segment2);

bool MeshVsMesh(const Mesh& mesh1, const Mesh& mesh2);