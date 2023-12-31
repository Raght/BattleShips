#include "Color.h"


olc::Pixel BlendColorsNoAlpha(olc::Pixel first_color, olc::Pixel second_color, BlendMode blend_mode)
{
    olc::Pixel result_color = first_color;
    switch (blend_mode)
    {
    case BlendMode::NORMAL:
        result_color = second_color;
        break;
    case BlendMode::REPAINT:
        result_color = second_color;
        break;
    case BlendMode::MULTIPLY:
        result_color.r *= second_color.r / 255.0f;
        result_color.g *= second_color.g / 255.0f;
        result_color.b *= second_color.b / 255.0f;
        break; 
    }
    
    return result_color;
}
