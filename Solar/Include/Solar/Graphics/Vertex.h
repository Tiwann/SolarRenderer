#pragma once
#include <Solar/Config.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


SOLAR_BEGIN
struct Vertex
{
    glm::vec3 mPosition;
    glm::vec2 mTexCoord;
    glm::vec3 mNormal;
    glm::vec4 mColor;
};
SOLAR_END