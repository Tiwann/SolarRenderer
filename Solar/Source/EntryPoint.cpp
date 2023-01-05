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
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,const void* userParam)
    {
        SOLAR_LOG_ERROR("[OpenGL] Error: {}\n" , message);
    }, nullptr);
#endif

    solar::Random::Seed();
    
    const std::vector<solar::Vertex> vertices
    {
        {{-0.5, -0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, solar::Color::Pink   },
        {{ 0.0f, 0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, solar::Color::Brown },
        {{ 0.5f,-0.5f, 0.0f },{0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, solar::Color::Cyan  },
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

    //GLuint fbo;
    //glCreateFramebuffers(1, &fbo);
    //glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    //// Create the texture
    //GLuint texture;
    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //// Attach the texture to the FBO
    //glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);


    // Initialize the ImGui context
    ImGui::CreateContext();
    // Set up the ImGui style
    ImGui::StyleColorsDark();
    // Initialize the ImGui IO structure
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Set up the ImGui platform and renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(*window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    
    while(!window.ShouldClose())
    {
        glClearColor(0.0, 0.0f, 0.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vao.Bind();
        shader.UseProgram();
        glDrawElements(GL_TRIANGLES, (GLsizei)ibo.Count(), GL_UNSIGNED_INT, nullptr);


        // Start a new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImGui::SetNextWindowPos({ 0.0f, 0.0f }, ImGuiCond_Always);
        ImGui::SetNextWindowSize({(float)window.Width(), (float)window.Height()});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
        flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoNavFocus;
        
        ImGui::Begin("Dockspace", nullptr, flags);
        ImGui::DockSpace(ImGui::GetID("Dockspace"));
        ImGui::PopStyleVar(3);

        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("New")) {}
                if(ImGui::MenuItem("Open")) {}
                if(ImGui::MenuItem("Save")) {}
                if(ImGui::MenuItem("Save as...")) {}
                ImGui::Separator();
                if(ImGui::MenuItem("Quit")) {}
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Edit"))
            {
                if(ImGui::MenuItem("Undo")) {}
                if(ImGui::MenuItem("Redo")) {}
                if(ImGui::MenuItem("Preferences")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
            ImGui::PopStyleVar(1);
        }
        ImGui::End();

        ImGui::Begin("Window");
        ImGui::Text("Test Windoow");
        ImGui::End();

        ImGui::Begin("Window2");
        ImGui::Text("Test Windoow");
        ImGui::End();
        
        // Render the frame
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
