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

#include "OpenGL/FrameBuffer.h"
#include "OpenGL/RenderCommand.h"
#include "OpenGL/Texture2D.h"
#include "Core/Tree.h"


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


    solar::Tree<const char*> tree("Root");
    auto& child0 = tree.GetRoot().PushChild("Apple");
    auto& child1 = tree.GetRoot().PushChild("Banana");
    auto& child2 = child0.PushChild("Pineapple");
    auto& child3 = child1.PushChild("Chocolate").PushChild("Strawberry");
 
    

    
   //solar::FrameBuffer framebuffer(solar::Texture2D({ 0, 0, solar::RGB }));
    

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
        static bool viewport_opened = true;
        static bool console_opened = true;
        static bool hierarchy_opened = true;
        static bool details_opened = true;

        solar::RenderCommand::Clear(solar::Color::Black);
        solar::RenderCommand::Clear(solar::ColorBuffer | solar::DepthBuffer);

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

            if(ImGui::BeginMenu("Show"))
            {
                ImGui::MenuItem("Viewport", nullptr, &viewport_opened);
                ImGui::MenuItem("Hierarchy", nullptr, &hierarchy_opened);
                ImGui::EndMenu();
            }
                
            ImGui::EndMainMenuBar();
            ImGui::PopStyleVar(1);
        }
        ImGui::End();
        
        
        
        if(viewport_opened)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
            ImGui::Begin("Viewport", &viewport_opened, ImGuiWindowFlags_NoScrollbar);
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
        }

        if(hierarchy_opened)
        {
            ImGui::Begin("Hierachy", &hierarchy_opened);
            if(ImGui::TreeNode("Test0"))
            {
                if(ImGui::TreeNode("OtherTest0"))
                {
                    if(ImGui::TreeNode("OtherOtherTest0"))
                    {
                        if(ImGui::Button("Close")) hierarchy_opened = false;
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("Test1"))
            {
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("Test2"))
            {
                ImGui::TreePop();
            }
            if(ImGui::TreeNode("Test3"))
            {
                ImGui::TreePop();
            }
            ImGui::End();
        }

        ImGui::Begin("TestWindow");
        tree.ForEach([](solar::TreeNode<const char*>& Node)
        {
            if(ImGui::TreeNode(Node.Data()))
            {
                ImGui::TreePop();
            }
        });
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
