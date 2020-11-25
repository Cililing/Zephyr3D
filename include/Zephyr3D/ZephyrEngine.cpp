#include "ZephyrEngine.h"
#include "Scene.h"

int zephyr::ZephyrEngine::Init() {
    // Initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window
    m_WindowManager.Initialize(1920, 1080, "Zephyr3D");
    if (!m_WindowManager) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window\n";
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(m_WindowManager);

    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_WindowManager, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_WindowManager, mouse_callback);
    glfwSetScrollCallback(m_WindowManager, scroll_callback);

    glfwSetInputMode(m_WindowManager, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return EXIT_SUCCESS;
}

void zephyr::ZephyrEngine::Destroy() {
    glfwSetWindowShouldClose(m_WindowManager, true);
    glfwTerminate();
}

zephyr::Timer& zephyr::ZephyrEngine::Time() {
    return m_Timer;
}

zephyr::IInput& zephyr::ZephyrEngine::Input() {
    return m_InputManager;
}

zephyr::IWindow& zephyr::ZephyrEngine::Window() {
    return m_WindowManager;
}
