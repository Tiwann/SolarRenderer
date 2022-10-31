#include "OpenGL/Texture2D.h"
#include <glad/gl.h>

solar::Texture2D::Texture2D()
{
    glCreateTextures(GL_TEXTURE_2D, 1, &mHandle);
    glBindTexture(GL_TEXTURE_2D, mHandle);
}
