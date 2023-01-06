#include <Core/Color.h>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

solar::Color::Color(std::uint32_t packed)
{
    r = std::clamp<float>((float)((packed >> 24) & 0xFF) / UCHAR_MAX, 0.0f, 1.0f);
    g = std::clamp<float>((float)((packed >> 16) & 0xFF) / UCHAR_MAX, 0.0f, 1.0f);
    b = std::clamp<float>((float)((packed >> 8) & 0xFF) / UCHAR_MAX, 0.0f, 1.0f);
    a = std::clamp<float>((float)(packed & 0xFF) / UCHAR_MAX, 0.0f, 1.0f);
}

solar::Color::Color(float red, float green, float blue, float alpha)
{
    r = std::clamp<float>(red, 0.0f, 1.0f);
    g = std::clamp<float>(green, 0.0f, 1.0f);
    b = std::clamp<float>(blue, 0.0f, 1.0f);
    a = std::clamp<float>(alpha, 0.0f, 1.0f);
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

solar::Color& solar::Color::operator=(const Color& color)
{
    if(&color == this) return *this;
    
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

solar::Color& solar::Color::operator=(uint32_t packed)
{
    r = std::clamp<float>((float)((packed >> 24) & 0xFF) / UCHAR_MAX, 0.0f, 1.0f);
    g = std::clamp<float>((float)((packed >> 16) & 0xFF) / UCHAR_MAX, 0.0f, 1.0f);
    b = std::clamp<float>((float)((packed >> 8) & 0xFF) / UCHAR_MAX, 0.0f, 1.0f);
    a = std::clamp<float>((float)(packed & 0xFF) / UCHAR_MAX, 0.0f, 1.0f);
    return *this;
}

solar::Color solar::Color::White    = 0xFFFFFFFF;
solar::Color solar::Color::Black    = 0x000000FF;
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





