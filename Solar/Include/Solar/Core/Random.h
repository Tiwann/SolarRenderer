#pragma once
#include <Solar/Config.h>
#include "Color.h"

SOLAR_BEGIN
class Random
{
public:
    static void Seed();
    static Color Color();
};
SOLAR_END