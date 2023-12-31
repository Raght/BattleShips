#include "olcPixelGameEngine.h"


class Bar
{
public:
	Bar(olc::vi2d position, olc::vi2d size, float value, float max_value, float min_value = 0);

	olc::vi2d position;
	olc::vi2d size;
	float value;
	float maxValue;
	float minValue = 0;
};