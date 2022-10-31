#include "OpenGL/FrameBuffer.h"
#include "OpenGL/Texture2D.h"
#include <glad/gl.h>

solar::FrameBuffer::FrameBuffer(const Texture2D& texture)
{
    glCreateFramebuffers(1, &mHandle);
    glBindFramebuffer(GL_FRAMEBUFFER, mHandle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texture, 0);
}

solar::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &mHandle);
}
