#include "Core/Random.h"
#include "Core/Color.h"
#include <ctime>
#include <cstdlib>


void solar::Random::Seed()
{
    std::srand((std::uint32_t)std::time(nullptr));
}

solar::Color solar::Random::Color()
{
    return solar::Color(0.0f, 0.0f, 0.0f, 0.0f);
}


