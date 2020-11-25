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
    m_Window.Initialize(1920, 1080, "Zephyr3D");
    if (!m_Window) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window\n";
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(m_Window);

    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_Window, mouse_callback);
    glfwSetScrollCallback(m_Window, scroll_callback);

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return EXIT_SUCCESS;
}

void zephyr::ZephyrEngine::StartScene(Scene& scene) {
    m_CurrentScene = &scene;

    scene.Initialize();
    scene.CreateScene();
    scene.Run();
    scene.Destroy();

    m_CurrentScene = nullptr;
}

void zephyr::ZephyrEngine::Destroy() {
    glfwSetWindowShouldClose(m_Window, true);
    glfwTerminate();
}

zephyr::Timer& zephyr::ZephyrEngine::Time() {
    return m_Time;
}

zephyr::InputManager& zephyr::ZephyrEngine::Input() {
    return m_Input;
}

zephyr::IWindow& zephyr::ZephyrEngine::Window() {
    return m_Window;
}

zephyr::rendering::IDrawManager& zephyr::ZephyrEngine::Rendering() {
    return m_CurrentScene->GetDrawManager();
}

zephyr::physics::IPhysicsManager& zephyr::ZephyrEngine::Physics() {
    return m_CurrentScene->GetPhysicsManager();
}

zephyr::resources::ResourcesManager& zephyr::ZephyrEngine::Resources() {
    return m_CurrentScene->GetResourcesManager();
}
