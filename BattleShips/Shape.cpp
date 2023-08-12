#include "Shape.h"


Shape::Shape()
{

}

Shape::Shape(const std::vector<olc::vf2d>& _points, olc::Pixel _color)
	: points(_points), color(_color)
{

}