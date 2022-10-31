#pragma once
#include <Solar/Config.h>
#include <string>
#include <string_view>
#include <array>
#include <functional>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

SOLAR_BEGIN
class Window
{
private:
    std::string mName = {};
    GLFWwindow* mHandle = nullptr;
    std::array<std::int32_t, 2> mSize = { 0, 0 };
    std::array<std::int32_t, 2> mPosition = { 0, 0 };
    bool mResizable = false;
    bool mMaximized = false;
    bool mHasFocus = false;
    bool mVSync = false;
public:
    Window(std::string name, std::int32_t width, std::int32_t height, bool resizable = true, bool vsync = true);
    ~Window();

    bool Create();
    void Bind() const;
    NODISCARD bool ShouldClose() const;
    void Destroy();
    void UpdateTitle(float framerate);
    void SwapBuffers() const;
    void SetVSync(bool enabled);
    NODISCARD std::uint32_t Width() const { return mSize[0]; }
    NODISCARD std::uint32_t Height() const { return mSize[1]; }
    GLFWwindow* operator*() const { return mHandle; }
    void SetCloseCallback(void (*callback)(GLFWwindow*)) const;
};
SOLAR_END