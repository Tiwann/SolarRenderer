#pragma once
#include <Config.h>

SOLAR_BEGIN
class Texture2D;
class FrameBuffer
{
private:
    Handle mHandle = 0;
public:
    FrameBuffer(const Texture2D& texture);
    ~FrameBuffer();
};
SOLAR_END