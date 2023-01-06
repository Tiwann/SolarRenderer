#pragma once
#include <Config.h>
#include <vector>
#include <glm/vec2.hpp>
#include "glad/gl.h"

SOLAR_BEGIN
enum TextureFormat : int32_t
{
    RGB = GL_RGB,
    RGBA = GL_RGBA,
    RG = GL_RG,
    BGR = GL_BGR,
    BGRA = GL_BGRA,
};

struct TextureParams
{
    int32_t width;
    int32_t height;
    TextureFormat format;
};

class Texture2D
{
private:
    Handle mHandle = 0;
    TextureParams mParams;
    std::vector<uint8_t> mData;
public:
    Texture2D(const TextureParams& params);
    ~Texture2D();
    void Bind() const;
    void Unbind() const;
    void SetData(const std::vector<uint8_t>& pixels);
    void Update();
    void SetParams(const TextureParams& params);

    const Handle& operator*() const { return mHandle; }
    NODISCARD const Handle& Handle() const { return mHandle; }
};
SOLAR_END