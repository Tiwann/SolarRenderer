#pragma once
#include <Solar/Config.h>
#include <vector>

SOLAR_BEGIN
class IndexBuffer
{
private:
    Handle mHandle = 0;
    std::uint32_t mCount = 0;
public:
    IndexBuffer();
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;
    void SetData(const std::uint32_t* data, std::size_t count);
    void SetData(const std::vector<std::uint32_t>& indices);
    NODISCARD std::uint32_t Count() const { return mCount; }
};
SOLAR_END