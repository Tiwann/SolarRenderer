#include "OpenGL/VertexArray.h"
#include <glad/gl.h>
#include <Graphics/Vertex.h>

solar::VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &mHandle);
}

solar::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mHandle);
}

void solar::VertexArray::Bind() const
{
    glBindVertexArray(mHandle);
}

void solar::VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void solar::VertexArray::SetVertexAttributes() const
{
    glBindVertexArray(mHandle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(solar::Vertex), (const void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(solar::Vertex), (const void*)12);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(solar::Vertex), (const void*)20);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(solar::Vertex), (const void*)32);
}

