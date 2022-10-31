#pragma once
#include <Config.h>

SOLAR_BEGIN
class Texture2D
{
private:
    Handle mHandle = 0;
public:
    Texture2D();
    
    const Handle& operator*() const { return mHandle; }
};
SOLAR_END