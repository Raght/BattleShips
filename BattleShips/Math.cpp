#include "Math.h"


float Mod(float a, float b)
{
	if (a > 0)
		return a - (int)(a / b) * b;
	return a - ((int)(a / b) - 1) * b;
}

bool InRange(float number, float range_min, float range_max)
{
	return range_min <= number && number <= range_max;
}

bool InRange2(float number, float middle, float range_span_from_middle)
{
	return middle - range_span_from_middle < number && number < middle + range_span_from_middle;
}

bool ApproximatelyEqual(float number1, float number2)
{
	return abs(number2 - number1) <= EPSILON;
}

bool Equal(float number1, float number2)
{
	return ApproximatelyEqual(number1, number2);
}

float Cap(float number, float minimum, float maximum)
{
	if (number < minimum)
		return minimum;
	else if (number > maximum)
		return maximum;
	return number;
}

int Cap(int number, int minimum, int maximum)
{
	if (number < minimum)
		return minimum;
	else if (number > maximum)
		return maximum;
	return number;
}

float Radians(float eulerAngle)
{
	return eulerAngle * PI / 180.0f;
}

float Degrees(float radians)
{
	return radians / PI * 180.0f;
}

float AngleBetween(olc::vf2d v1, olc::vf2d v2)
{
	return acosf((v1.dot(v2)) / (v1.mag() * v2.mag()));
}

float AngleBetweenToRotateAntiClockwise(olc::vf2d unit_vector_from, olc::vf2d unit_vector_to)
{
	std::complex<float> c1 = { unit_vector_from.x, unit_vector_from.y };
	std::complex<float> c1_conjugate = { unit_vector_from.x, -unit_vector_from.y };
	std::complex<float> c2 = { unit_vector_to.x, unit_vector_to.y };
	c2 *= c1_conjugate;
	float x = c2.real(), y = c2.imag();
	float angle = AngleBetween(unit_vector_from, unit_vector_to);
	if (y > 0)
		return angle;
	else if (y == 0)
		return (Equal(x, 1)) ? 0 : PI;
	else
		return 2 * PI - angle;
}

olc::vf2d RotateVector(olc::vf2d v, float radians)
{
	//return { v.x * cos(radians) - v.y * sin(radians),
	//		 v.x * sin(radians) + v.y * cos(radians) };

	std::complex<float> d = { v.x, v.y };
	std::complex<float> r = { cosf(radians), sinf(radians) };
	std::complex<float> new_d = d * r;
	return { new_d.real(), new_d.imag() };
}


olc::vf2d RotatePointAroundOrigin(olc::vf2d point, olc::vf2d origin, float radians)
{
	point -= origin;
	point = RotateVector(point, radians);
	point += origin;

	return point;
}

