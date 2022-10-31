#include "Solar/OpenGL/IndexBuffer.h"
#include <glad/gl.h>

solar::IndexBuffer::IndexBuffer()
{
    glCreateBuffers(1, &mHandle);
}

solar::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &mHandle);
}

void solar::IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandle);
}

void solar::IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void solar::IndexBuffer::SetData(const std::uint32_t* data, std::size_t count)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(count * sizeof(std::uint32_t)), data, GL_STATIC_DRAW);
    mCount = (std::uint32_t)count;
}

void solar::IndexBuffer::SetData(const std::vector<std::uint32_t>& indices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(indices.size() * sizeof(std::uint32_t)), indices.data(), GL_STATIC_DRAW);
    mCount = (std::uint32_t)indices.size();
}
