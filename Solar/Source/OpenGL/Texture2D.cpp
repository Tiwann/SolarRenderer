#include "OpenGL/Texture2D.h"
#include <glad/gl.h>


solar::Texture2D::Texture2D(const TextureParams& params)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &mHandle);
    mParams = params;
    (void)mData;
}

void solar::Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, mHandle);
}

void solar::Texture2D::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void solar::Texture2D::SetData(const std::vector<uint8_t>& pixels)
{
    mData = pixels;
    glBindTexture(GL_TEXTURE_2D, mHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, mParams.format, mParams.width, mParams.height, 0, mParams.format, GL_UNSIGNED_BYTE,  mData.empty() ? nullptr : mData.data());
    glBindTexture(GL_TEXTURE_2D, 0);

}

void solar::Texture2D::Update()
{
    glBindTexture(GL_TEXTURE_2D, mHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, mParams.format, mParams.width, mParams.height, 0, mParams.format, GL_UNSIGNED_BYTE,  mData.empty() ? nullptr : mData.data());
    glBindTexture(GL_TEXTURE_2D, 0);
}

void solar::Texture2D::SetParams(const TextureParams& params)
{
    mParams = params;
}
