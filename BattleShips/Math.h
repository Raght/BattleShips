#pragma once
#include <cmath>
#include <complex>
#include "olcPixelGameEngine.h"


inline const float PI = 3.141592653589793238462643383279f;
inline const float EPSILON = 1e-5f;


float Mod(float a, float b);

bool InRange(float number, float range_min, float range_max);

bool InRange2(float number, float middle, float range_span_from_middle);

bool ApproximatelyEqual(float number1, float number2);

bool Equal(float number1, float number2);

float Cap(float number, float minimum, float maximum);

int Cap(int number, int minimum, int maximum);

float Radians(float eulerAngle);

float Degrees(float radians);

float AngleBetween(olc::vf2d v1, olc::vf2d v2);

float AngleBetweenToRotateAntiClockwise(olc::vf2d unit_vector_from, olc::vf2d unit_vector_to);

olc::vf2d RotateVector(olc::vf2d v, float radians);

olc::vf2d RotateVectorAroundPoint(olc::vf2d v, olc::vf2d point, float radians);