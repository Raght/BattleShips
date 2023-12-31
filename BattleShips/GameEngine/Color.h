#pragma once
#include "olcPixelGameEngine.h"


enum class BlendMode { NORMAL, REPAINT, MULTIPLY };


olc::Pixel BlendColorsNoAlpha(olc::Pixel first_color, olc::Pixel second_color, BlendMode blend_mode);
