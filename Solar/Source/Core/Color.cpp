#include <Core/Color.h>
#include <climits>
#include <cstdlib>
#include <ctime>

solar::Color::Color(std::uint32_t packed)
{
    r = (float)((packed >> 24) & 0xFF) / UCHAR_MAX;
    g = (float)((packed >> 16) & 0xFF) / UCHAR_MAX;
    b = (float)((packed >> 8) & 0xFF) / UCHAR_MAX;
    a = (float)(packed & 0xFF) / UCHAR_MAX;
}

solar::Color::Color(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

solar::Color::Color(float hue, float value, float saturation)
{
    SOLAR_ASSERT(false, "Hue Value Saturation not yet implemented!");
}

solar::Color::operator std::uint32_t() const
{
    SOLAR_ASSERT(false, "operator unsigned int not yet implemented!");
    return {};
}
