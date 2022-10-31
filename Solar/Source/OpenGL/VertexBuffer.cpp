#include "Solar/OpenGL/VertexBuffer.h"
#include <glad/gl.h>

#include "Graphics/Vertex.h"

solar::VertexBuffer::VertexBuffer()
{
    glCreateBuffers(1, &mHandle);
}


solar::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &mHandle);
}

void solar::VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, mHandle);
}

void solar::VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void solar::VertexBuffer::SetData(const Vertex* vertices, std::size_t count) const
{
    glBindBuffer(GL_ARRAY_BUFFER, mHandle);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vertex) * count), vertices, GL_STATIC_DRAW);
}

void solar::VertexBuffer::SetData(const std::vector<Vertex>& vertices) const
{
    glBindBuffer(GL_ARRAY_BUFFER, mHandle);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);
}

