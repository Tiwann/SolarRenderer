#pragma once
#include "Config.h"
#include <glm/vec4.hpp>

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
    operator glm::vec4() const;

    static Color Black;
    static Color White;
    static Color Red;
    static Color Green;
    static Color Blue;
    static Color Yellow;
    static Color Magenta;
    static Color Cyan;
    static Color Orange;
    static Color Purple;
    static Color Pink;
    static Color Gray;
    static Color Brown;
};
SOLAR_END
