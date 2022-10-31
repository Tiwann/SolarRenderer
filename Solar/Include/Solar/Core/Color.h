#pragma once
#include "Config.h"

SOLAR_BEGIN
class Color
{
public:
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 0.0f;
    
    
public:
    Color(std::uint32_t packed);
    Color(float red, float green, float blue, float alpha);
    Color(float hue, float value, float saturation);
    
    operator std::uint32_t() const;
};
SOLAR_END
