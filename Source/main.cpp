// glfw_imgui_template.cpp
// Basic GLFW + OpenGL 3.3 Core + Dear ImGui application loop using **GLEW** for function loading
// -------------------------------------------------------------------------------------------
// Build example (Linux / macOS):
// g++ glfw_imgui_template.cpp -I/path/to/imgui -I/usr/include -lglfw -lGLEW -ldl -lGL -pthread -o app
// Make sure Dear ImGui backend files (imgui_impl_glfw.cpp, imgui_impl_opengl3.cpp, imgui*.cpp) are compiled in as well.
// Windows (MSVC) users: link opengl32.lib, glfw3.lib, glew32( s ) .lib and add imgui sources to the project.

#include <cstdio>
#include <cstdlib>

#define GLEW_STATIC            // Remove if linking against the shared GLEW library
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static void glfw_error_callback(int error, const char* description)
{
    std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main()
{
    // ---------------------------------------------------------------------
    // GLFW: initialize and configure
    // ---------------------------------------------------------------------
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return EXIT_FAILURE;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif

    const int window_width = 1280;
    const int window_height = 720;
    GLFWwindow* window = glfwCreateWindow(window_width, window_height,
        "ImGui GLFW OpenGL3 (GLEW) Template", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // ---------------------------------------------------------------------
    // GLEW: load all OpenGL function pointers
    // ---------------------------------------------------------------------
    glewExperimental = GL_TRUE; // Ensure access to modern OpenGL functions
    if (glewInit() != GLEW_OK)
    {
        std::fprintf(stderr, "Failed to initialize GLEW\n");
        return EXIT_FAILURE;
    }

    // After GLEW initialization, clear the GL error flag generated on core profiles
    glGetError();

    // ---------------------------------------------------------------------
    // Dear ImGui: setup context
    // ---------------------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark(); // Global style

    // Initialize Dear ImGui back‑ends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // ---------------------------------------------------------------------
    // Main loop
    // ---------------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        // Poll events
        glfwPollEvents();

        // Start Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Example ImGui window
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a basic template window using GLEW.");
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // ---------------------------------------------------------------------
    // Cleanup
    // ---------------------------------------------------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
