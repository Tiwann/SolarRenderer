#include "Core/Window.h"
#include "Core/Log.h"

solar::Window::Window(std::string name, std::int32_t width, std::int32_t height, bool resizable, bool vsync)
    : mName(std::move(name)), mSize({ width, height }), mResizable(resizable), mVSync(vsync)
{
    glfwWindowHint(GLFW_RESIZABLE, mResizable);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_SAMPLES, 8);
}

solar::Window::~Window()
{
    if(mHandle)
    {
        glfwDestroyWindow(mHandle);
        mHandle = nullptr;
    }
}

bool solar::Window::Create()
{
#if defined(SOLAR_WINDOWS)
    mName.append(" | Windows");
#elif defined(SOLAR_LINUX)
    mName.append(" | Linux");
#endif

#if defined(SOLAR_DEBUG)
    mName.append(" Debug");
#elif defined(SOLAR_RELEASE)
    mName.append(" Release");
#endif

    
    mHandle = glfwCreateWindow(mSize[0], mSize[1], mName.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(mHandle, this);
    
    glfwSetWindowSizeCallback(mHandle, [](GLFWwindow* window, std::int32_t width, std::int32_t height)
    {
        Window* const theWindow = (Window*)glfwGetWindowUserPointer(window);
        theWindow->mSize[0] = width;
        theWindow->mSize[1] = height;
#if defined(SOLAR_DEBUG) && defined(SOLAR_LOG_WINDOW_CALLBACKS)
        SOLAR_LOG_TRACE("[GLFW] Window size({}, {}})\n", theWindow->mSize[0], theWindow->mSize[1]);
#endif
    });

    
    glfwSetWindowMaximizeCallback(mHandle, [](GLFWwindow* window, std::int32_t maximized)
    {
        Window* const theWindow = (Window*)glfwGetWindowUserPointer(window);
        theWindow->mMaximized = maximized;
#if defined(SOLAR_DEBUG) && defined(SOLAR_LOG_WINDOW_CALLBACKS)
        if((bool)maximized == true) SOLAR_LOG_TRACE("[GLFW] Window maximed.\n");
#endif
    });

    glfwSetWindowFocusCallback(mHandle, [](GLFWwindow* window, std::int32_t focus)
    {
        Window* const theWindow = (Window*)glfwGetWindowUserPointer(window);
        theWindow->mHasFocus = focus;
#if defined(SOLAR_DEBUG) && defined(SOLAR_LOG_WINDOW_CALLBACKS)
    if((bool)focus == true) SOLAR_LOG_TRACE("[GLFW] Window has focus.\n");
    else SOLAR_LOG_TRACE("[GLFW] Window lose focus.\n");
#endif
    });

    glfwSetWindowPosCallback(mHandle, [](GLFWwindow* window, std::int32_t posx, std::int32_t posy)
    {
        Window* const theWindow = (Window*)glfwGetWindowUserPointer(window);
        theWindow->mPosition[0] = posx;
        theWindow->mPosition[1] = posy;
#if defined(SOLAR_DEBUG) && defined(SOLAR_LOG_WINDOW_CALLBACKS)
SOLAR_LOG_TRACE("[GLFW] Window position({}, {}})\n", theWindow->mPosition[0], theWindow->mPosition[1]);
#endif
    });

    glfwSetFramebufferSizeCallback(mHandle, [](GLFWwindow* window, std::int32_t width, std::int32_t height)
    {
        glViewport(0, 0, width, height);
    });
    return mHandle;
}

void solar::Window::Bind() const
{
    glfwMakeContextCurrent(mHandle);
}

bool solar::Window::ShouldClose() const
{
    return glfwWindowShouldClose(mHandle);
}

void solar::Window::Destroy()
{
    if(mHandle)
    {
        glfwDestroyWindow(mHandle);
        mHandle = nullptr;
    }
}

void solar::Window::UpdateTitle(float framerate)
{
    const std::string newTitle = fmt::format("{} | Delta: {}", mName, framerate);
    glfwSetWindowTitle(mHandle, newTitle.c_str());
}

void solar::Window::SwapBuffers() const
{
    glfwSwapBuffers(mHandle);
}

void solar::Window::SetVSync(bool enabled)
{
    glfwSwapInterval(mVSync = enabled);
}

void solar::Window::SetCloseCallback(void (*callback)(GLFWwindow*)) const
{
    glfwSetWindowCloseCallback(mHandle, callback);
}


