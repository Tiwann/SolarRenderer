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

#include "OpenGL/RenderCommand.h"
#include "OpenGL/Texture2D.h"


int SOLAR_MAIN
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

#if defined(SOLAR_DEBUG)
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, int32_t length, const GLchar* message,const void* userParam)
    {
        SOLAR_LOG_ERROR("[OpenGL] Error: {}\n" , message);
    }, nullptr);
#endif

    solar::Random::Seed();
    
    const std::vector<solar::Vertex> vertices
    {
        {{-0.5, -0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, solar::Color::Red   },
        {{ 0.0f, 0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, solar::Color::Green },
        {{ 0.5f,-0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, solar::Color::Blue  },
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

    solar::Texture2D texture0;
    texture0.Bind();
    

    GLuint fbo;
    glCreateFramebuffers(1, &fbo);

    // Create the texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Attach the texture to the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)(io);
    io.ConfigFlags = ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(*window, true);
    ImGui_ImplOpenGL3_Init("#version 450 core");
    
    
    while(!window.ShouldClose())
    {
        solar::RenderCommand::Clear(solar::Color::Black);


        glm::uint32 bitfield0 = solar::BufferTypeColor | solar::BufferTypeDepth;
        glm::uint32 bitfield1 = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        GLbitfield bitfield2 = solar::BufferTypeColor | solar::BufferTypeDepth;
        GLbitfield bitfield3 = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        
        solar::RenderCommand::Clear(solar::BufferTypeDepth | solar::BufferTypeColor);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
        ImGui::Begin("Window");
        ImGui::PopStyleVar(1);
        
        // Update texture
        glBindTexture(GL_TEXTURE_2D, texture);
        const ImVec2 windowSize = ImGui::GetWindowSize();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int32_t)windowSize.x, (int32_t)windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE,  nullptr);

        // Draw to framebuffer
        glViewport(0, 0, (int32_t)windowSize.x, (int32_t)windowSize.y);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        vao.Bind();
        shader.UseProgram();
        glDrawElements(GL_TRIANGLES, (int32_t)ibo.Count(), GL_UNSIGNED_INT, nullptr);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        
        ImGui::Image((ImTextureID)texture, windowSize, { 1.0f, 1.0f}, {0.0f, 0.0f});
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        
        
        window.SwapBuffers();
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    window.Destroy();
    glfwTerminate();
    return 0;
}
