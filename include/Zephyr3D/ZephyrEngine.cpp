#include "ZephyrEngine.h"
#include "Scene.h"

void zephyr::ZephyrEngine::Initialize(unsigned int window_width, unsigned int window_height, const std::string& window_title) {
    // Initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_WindowManager.Initialize(window_width, window_height, window_title);

    // Load glad
    auto glad_result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    m_InputManager.Initialize();
}

void zephyr::ZephyrEngine::Destroy() {
    glfwSetWindowShouldClose(m_WindowManager.Handle(), true);
    glfwTerminate();
}

zephyr::IClock& zephyr::ZephyrEngine::Time() {
    return m_Clock;
}

zephyr::IInput& zephyr::ZephyrEngine::Input() {
    return m_InputManager;
}

zephyr::IWindow& zephyr::ZephyrEngine::Window() {
    return m_WindowManager;
}

zephyr::resources::ResourcesManager& zephyr::ZephyrEngine::Resources() {
    return m_ResourceManager;
}
