#include "OpenGL/RenderCommand.h"
#include <glm/vec4.hpp>

void solar::RenderCommand::Clear(uint32_t Buffers)
{
    glClear(Buffers);
}

void solar::RenderCommand::Clear(Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}
