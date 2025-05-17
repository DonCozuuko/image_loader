// glfw_imgui_template.cpp
// Basic GLFW + OpenGL 3.3 Core + Dear ImGui application loop using **GLEW** for function loading
// -------------------------------------------------------------------------------------------
// Build example (Linux / macOS):
// g++ glfw_imgui_template.cpp -I/path/to/imgui -I/usr/include -lglfw -lGLEW -ldl -lGL -pthread -o app
// Make sure Dear ImGui backend files (imgui_impl_glfw.cpp, imgui_impl_opengl3.cpp, imgui*.cpp) are compiled in as well.
// Windows (MSVC) users: link opengl32.lib, glfw3.lib, glew32( s ) .lib and add imgui sources to the project.

// glfw_imgui_template.cpp
// Basic GLFW + OpenGL 3.3 Core + Dear ImGui sample that relies **only on GLFW** for context creation
// and uses ImGui's built‑in custom loader to fetch OpenGL function pointers via `glfwGetProcAddress`.
// No GLAD, GLEW, GL3W, or other external loaders are required.
// -----------------------------------------------------------------------------------------------
// Build example (Linux / macOS):
//   g++ glfw_imgui_template.cpp -I/path/to/imgui -I/usr/include -lglfw -ldl -lGL -pthread -o app
// Windows (MSVC) users:
//   • Add imgui*.cpp, imgui_impl_glfw.cpp, imgui_impl_opengl3.cpp to the project
//   • Link opengl32.lib and glfw3.lib
//   • Define IMGUI_IMPL_OPENGL_LOADER_CUSTOM (already done below)
//
// ImGui ≥ 1.90 includes a tiny self‑loader when you define IMGUI_IMPL_OPENGL_LOADER_CUSTOM and call
// `ImGui_ImplOpenGL3_InitLoader()` with your own `glfwGetProcAddress` wrapper, so we truly depend on
// **nothing but GLFW**.

#include <cstdio>
#include <cstdlib>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM   // Tell ImGui we'll supply our own loader
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// The header below *must* be included **after** the macro above so it generates the function pointer table
#include <imgui_impl_opengl3_loader.h>

#include <glfw/include/GLFW/glfw3.h>

// -------------------------------------------------------------------------------------------------
// Minimal loader that redirects to glfwGetProcAddress. ImGui will use this to resolve core/ARB funcs.
// -------------------------------------------------------------------------------------------------
static void* glfw_loader(const char* function_name)
{
    return reinterpret_cast<void*>(glfwGetProcAddress(function_name));
}

static void glfw_error_callback(int error, const char* description)
{
    std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main()
{
    // ---------------------------------------------------------------------------------------------
    // GLFW: initialize and configure
    // ---------------------------------------------------------------------------------------------
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
        "ImGui GLFW OpenGL3 (GLFW‑only) Template", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // ---------------------------------------------------------------------------------------------
    // ImGui: setup context and load OpenGL functions through our custom loader
    // ---------------------------------------------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    // Hook ImGui to GLFW
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    // This line magically fills ImGui's internal GL function pointers by calling `glfw_loader`.
    if (!ImGui_ImplOpenGL3_InitLoader(glfw_loader))
    {
        std::fprintf(stderr, "Failed to load OpenGL functions via GLFW loader\n");
        return EXIT_FAILURE;
    }

    ImGui_ImplOpenGL3_Init("#version 330");

    // ---------------------------------------------------------------------------------------------
    // Main loop
    // ---------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Example window
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This template uses only GLFW – no GLEW/GLAD/GL3W.");
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

    // ---------------------------------------------------------------------------------------------
    // Cleanup
    // ---------------------------------------------------------------------------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
