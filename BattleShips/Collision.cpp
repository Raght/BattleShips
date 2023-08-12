#include "Collision.h"



bool SegmentVsSegment(Segment segment1, Segment segment2)
{
	olc::vf2d ray1_origin_to_p1 = segment2.p1 - segment1.p1;
	olc::vf2d ray1_origin_to_p2 = segment2.p2 - segment1.p1;
	olc::vf2d ray1_direction = segment1.p2 - segment1.p1;

	float ray1_cross1 = ray1_direction.cross(ray1_origin_to_p1);
	float ray1_cross2 = ray1_direction.cross(ray1_origin_to_p2);
	bool line_intersects_segment = ray1_cross1 * ray1_cross2 <= 0.0f;

	float ray1_cross3 = ray1_origin_to_p1.cross(ray1_origin_to_p2);
	bool ray1_points_towards_segment = ray1_cross3 * ray1_cross1 <= 0.0f; // && cross3 * cross2 >= 0.0f;

	olc::vf2d ray2_origin_to_p1 = segment2.p1 - segment1.p2;
	olc::vf2d ray2_origin_to_p2 = segment2.p2 - segment1.p2;
	olc::vf2d ray2_direction = segment1.p1 - segment1.p2;
	
	float ray2_cross1 = ray2_direction.cross(ray2_origin_to_p1);
	float ray2_cross3 = ray2_origin_to_p1.cross(ray2_origin_to_p2);
	bool ray2_points_towards_segment = ray2_cross3 * ray2_cross1 <= 0.0f; // && cross3 * cross2 >= 0.0f;

	//bool ray2_points_towards_segment = true;

	return line_intersects_segment && ray1_points_towards_segment && ray2_points_towards_segment;
}

bool MeshVsMesh(const Mesh& mesh1, const Mesh& mesh2)
{
	for (const Shape& polygon1 : mesh1.polygons)
	{
		for (const Shape& polygon2 : mesh2.polygons)
		{
			for (int i1 = 0; i1 < polygon1.points.size(); i1++)
			{
				Segment segment1;
				if (i1 != polygon1.points.size() - 1)
					segment1 = { polygon1.points[i1], polygon1.points[i1 + 1] };
				else
					segment1 = { polygon1.points[i1], polygon1.points[0] };

				for (int i2 = 0; i2 < polygon2.points.size(); i2++)
				{
					Segment segment2;
					if (i2 != polygon2.points.size() - 1)
						segment2 = { polygon2.points[i2], polygon2.points[i2 + 1] };
					else
						segment2 = { polygon2.points[i2], polygon2.points[0] };

					if (SegmentVsSegment(segment1, segment2))
						return true;
				}
			}
		}
	}

	return false;
}
