#include "OpenGL/FrameBuffer.h"
#include "OpenGL/Texture2D.h"
#include <glad/gl.h>

solar::FrameBuffer::FrameBuffer()
{
    glCreateFramebuffers(1, &mHandle);
}

solar::FrameBuffer::FrameBuffer(const Texture2D& texture)
{
    glCreateFramebuffers(1, &mHandle);
    AttachTexture(texture);
}

solar::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &mHandle);
}

void solar::FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, mHandle);
}

void solar::FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void solar::FrameBuffer::AttachTexture(const Texture2D& texture)
{
    Bind();
    mAttachedTexture = std::make_shared<Texture2D>(texture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mAttachedTexture->Handle(), 0);
    Unbind();
}
