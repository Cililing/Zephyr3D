#include "Engine.h"

// Global objects
Input g_Input;
Window g_Window;

int Engine::Init() {
    // Initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window
    g_Window.Initialize(1920, 1080, "Zephyr3D");
    if (!g_Window) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window\n";
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(g_Window);

    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }

    // Set callbacks
    glfwSetFramebufferSizeCallback(g_Window, framebuffer_size_callback);
    glfwSetCursorPosCallback(g_Window, mouse_callback);
    glfwSetScrollCallback(g_Window, scroll_callback);

    glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return EXIT_SUCCESS;
}

void Engine::StartScene() {

}

void Engine::Destroy() {
    glfwSetWindowShouldClose(g_Window, true);
    glfwTerminate();
}

Time& Engine::GetTime() {
    return m_Time;
}

Input& Engine::GetInput() {
    return m_Input;
}

Window& Engine::GetWindow() {
    return m_Window;
}
