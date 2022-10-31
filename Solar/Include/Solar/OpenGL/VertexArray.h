#pragma once
#include <Solar/Config.h>

SOLAR_BEGIN
class VertexArray
{
private:
    Handle mHandle = 0;
public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    void SetVertexAttributes() const;
};
SOLAR_END

