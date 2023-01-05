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

solar::Color::operator glm::vec4() const
{
    return { r, g, b, a };
}

solar::Color solar::Color::Black    = 0xFFFFFFFF;
solar::Color solar::Color::White    = 0x000000FF;
solar::Color solar::Color::Red      = 0xFF0000FF;
solar::Color solar::Color::Green    = 0x00FF00FF;
solar::Color solar::Color::Blue     = 0x0000FFFF;
solar::Color solar::Color::Yellow   = 0xFFFF00FF;
solar::Color solar::Color::Magenta  = 0xFF00FFFF;
solar::Color solar::Color::Cyan     = 0x00FFFFFF;
solar::Color solar::Color::Orange   = 0xFF8000FF;
solar::Color solar::Color::Purple   = 0xA020F0FF;
solar::Color solar::Color::Pink     = 0xFFC0CBFF;
solar::Color solar::Color::Gray     = 0x808080FF;
solar::Color solar::Color::Brown    = 0x964B00FF;










;





