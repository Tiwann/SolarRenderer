#pragma once
#include <Config.h>
#include <memory>

SOLAR_BEGIN
class Texture2D;

class FrameBuffer
{
private:
    Handle mHandle = 0;
    std::shared_ptr<Texture2D> mAttachedTexture;
public:
    FrameBuffer();
    FrameBuffer(const Texture2D& texture);
    ~FrameBuffer();

    void Bind() const;
    void Unbind() const;
    void AttachTexture(const Texture2D& texture);
};
SOLAR_END