#include "Bar.h"


Bar::Bar(olc::vi2d position, olc::vi2d size, float* value_ptr, float max_value, float min_value)
	: position(position), size(size), valuePtr(value_ptr), maxValue(max_value), minValue(min_value)
{

}