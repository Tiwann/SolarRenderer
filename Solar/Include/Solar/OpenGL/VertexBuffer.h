#pragma once
#include <Solar/Config.h>
#include <vector>

SOLAR_BEGIN
struct Vertex;

class VertexBuffer
{
private:
    Handle mHandle = 0;
public:
    VertexBuffer();
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
    void SetData(const Vertex* vertices, std::size_t count) const;
    void SetData(const std::vector<Vertex>& vertices) const;
};
SOLAR_END