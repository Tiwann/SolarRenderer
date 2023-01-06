#pragma once
#include <Solar/Config.h>
#include <Core/Color.h>
#include <glad/GL.h>
#include <vector>

SOLAR_BEGIN
enum : uint32_t
{
    BufferTypeColor = GL_COLOR_BUFFER_BIT,
    BufferTypeDepth = GL_DEPTH_BUFFER_BIT
};

class RenderCommand
{
public:
    static void Clear(uint32_t Buffers);
    static void Clear(Color color);
};
SOLAR_END