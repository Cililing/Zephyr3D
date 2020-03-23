#include "Engine.h"

int zephyr::Engine::Init() {
    // Initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window
    Engine::Instance().GetWindow().Initialize(1920, 1080, "Zephyr3D");
    if (!Engine::Instance().GetWindow()) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window\n";
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(Engine::Instance().GetWindow());

    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }

    // Set callbacks
    glfwSetFramebufferSizeCallback(Engine::Instance().GetWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(Engine::Instance().GetWindow(), mouse_callback);
    glfwSetScrollCallback(Engine::Instance().GetWindow(), scroll_callback);

    glfwSetInputMode(Engine::Instance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return EXIT_SUCCESS;
}

void zephyr::Engine::StartScene() {

}

void zephyr::Engine::Destroy() {
    glfwSetWindowShouldClose(Engine::Instance().GetWindow(), true);
    glfwTerminate();
}

Time& zephyr::Engine::GetTime() {
    return m_Time;
}

Input& zephyr::Engine::GetInput() {
    return m_Input;
}

Window& zephyr::Engine::GetWindow() {
    return m_Window;
}
