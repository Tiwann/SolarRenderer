#include <iostream>
#include <glad/gl.h>
#include <Solar/Core.h>
#include <Solar/OpenGL.h>
#include <Solar/Graphics.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include "Core/ObjParser.h"
#include <spdlog/spdlog.h>
#include <filesystem>

#include "spdlog/sinks/stdout_color_sinks.h"

static void ImGuiStyleDark()
{
  ImVec4* colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
  colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_DockingPreview]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_DockingEmptyBg]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowPadding                     = ImVec2(8.00f, 8.00f);
  style.FramePadding                      = ImVec2(5.00f, 2.00f);
  style.CellPadding                       = ImVec2(6.00f, 6.00f);
  style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
  style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
  style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
  style.IndentSpacing                     = 25;
  style.ScrollbarSize                     = 15;
  style.GrabMinSize                       = 10;
  style.WindowBorderSize                  = 1;
  style.ChildBorderSize                   = 1;
  style.PopupBorderSize                   = 1;
  style.FrameBorderSize                   = 1;
  style.TabBorderSize                     = 1;
  style.WindowRounding                    = 7;
  style.ChildRounding                     = 4;
  style.FrameRounding                     = 3;
  style.PopupRounding                     = 4;
  style.ScrollbarRounding                 = 9;
  style.GrabRounding                      = 3;
  style.LogSliderDeadzone                 = 4;
  style.TabRounding                       = 4;
}

#if defined(SOLAR_WINDOWS)
INT CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    solar::Log::Init();

    
    // Initialize GLFW
    SOLAR_ASSERT(glfwInit(), "[GLFW] Failed to initialize GLFW.");
    glfwSetErrorCallback([](std::int32_t code, const char* message)
    {
        SOLAR_LOG_ERROR("[GLFW] Error {}: {}\n", code, message);
        SOLAR_ASSERT(false, message);
    });
    SOLAR_LOG_INFO("[GLFW] GLFW init successful!");

    // Creating a window
    solar::Window window("Solar Renderer", 1600, 900);
    SOLAR_ASSERT(window.Create(), "[GLFW] Failed to create window.");
    window.Bind();

    // Loading OpenGl extensions
    SOLAR_ASSERT(gladLoadGL(glfwGetProcAddress), "[OPENGL] Failed to initialize OpenGL context!");
    SOLAR_LOG_INFO("[OpenGL] OpenGL extensions loading successful!");

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

#if defined(SOLAR_DEBUG)
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,const void* userParam)
    {
        SOLAR_LOG_ERROR("[OpenGL] Error: {}\n" , message);
    }, nullptr);
#endif

    solar::Random::Seed();
    
    const std::vector<solar::Vertex> vertices
    {
        {{-0.5, -0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},{1.0f, 0.0f, 0.0f, 1.0f}},
        {{ 0.0f, 0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},{0.0f, 1.0f, 0.0f, 1.0f}},
        {{ 0.5f,-0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
    };

    const std::vector<std::uint32_t> indices { 0, 2, 1 };
    
    solar::VertexArray vao;
    solar::VertexBuffer vbo;
    solar::IndexBuffer ibo;
    
    vao.Bind();
    vbo.SetData(vertices);
    ibo.SetData(indices);
    vao.SetVertexAttributes();
    
    solar::Shader shader(R"(Shaders\Test\Test.vert)", R"(Shaders\Test\Test.frag)");
    shader.Compile();
    shader.Link();

    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.DisplaySize = { (float)window.Width(), (float)window.Height() };
        ImGui_ImplGlfw_InitForOpenGL(*window, true);
        ImGui_ImplOpenGL3_Init("#version 460 core");
        ImGuiStyleDark();
    }
    
    while(!window.ShouldClose())
    {
        glClearColor(0.0, 0.0f, 0.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vao.Bind();
        shader.UseProgram();
        glDrawElements(GL_TRIANGLES, (GLsizei)ibo.Count(), GL_UNSIGNED_INT, nullptr);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.SwapBuffers();
        glfwPollEvents();
    }
    
    window.Destroy();
    glfwTerminate();
    return 0;
}
#else
int main(const int argc, const char** argv)
{
    solar::Log::Init();
    std::vector<solar::ObjMesh> ObjMeshes;
    solar::LoadObj("Assets/Meshes/sonic.obj",ObjMeshes);
    
    
    // Initialize GLFW
    SOLAR_ASSERT(glfwInit(), "[GLFW] Failed to initialize GLFW.");
    glfwSetErrorCallback([](std::int32_t code, const char* message)
    {
        SOLAR_LOG_ERROR("[GLFW] Error {}: {}\n", code, message);
        SOLAR_ASSERT(false, message);
    });
    SOLAR_LOG_INFO("[GLFW] GLFW init successful!");

    // Creating a window
    solar::Window window("Solar Renderer", 1600, 900);
    SOLAR_ASSERT(window.Create(), "[GLFW] Failed to create window.");
    window.Bind();

    // Loading OpenGl extensions
    SOLAR_ASSERT(gladLoadGL(glfwGetProcAddress), "[OPENGL] Failed to initialize OpenGL context!");
    SOLAR_LOG_INFO("[OpenGL] OpenGL extensions loading successful!");

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

#if defined(SOLAR_DEBUG)
    glEnable(GL_DEBUG_OUTPUT);

    auto messageCallback = [](GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam)
    {
        SOLAR_LOG_ERROR("[OpenGL] Error: {}\n" , message);
    };
    glDebugMessageCallback(messageCallback, nullptr);
#endif

    solar::Random::Seed();

    const std::vector<solar::Vertex> vertices
    {
        {{-0.5, -0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},{1.0f, 0.0f, 0.0f, 1.0f}},
        {{ 0.0f, 0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},{0.0f, 1.0f, 0.0f, 1.0f}},
        {{ 0.5f,-0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
    };

    const std::vector<std::uint32_t> indices { 0, 2, 1 };
    
    const solar::VertexArray vao;
    vao.Bind();
    
    const solar::VertexBuffer vbo(vertices);
    vao.SetVertexAttributes();
    
    const solar::IndexBuffer ibo(indices);
    solar::Shader shader(R"(Shaders\Test\Test.vert)", R"(Shaders\Test\Test.frag)");
    shader.Compile();
    shader.Link();

    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.DisplaySize = { (float)window.Width(), (float)window.Height() };
        ImGui_ImplGlfw_InitForOpenGL(*window, true);
        ImGui_ImplOpenGL3_Init("#version 460 core");
        ImGuiStyleDark();
    }
    
    while(!window.ShouldClose())
    {
        glClearColor(0.0, 0.0f, 0.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.UseProgram();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window.SwapBuffers();
        glfwPollEvents();
    }
    
    window.Destroy();
    glfwTerminate();
    return 0;
}
#endif
