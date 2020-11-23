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
    ZephyrEngine::Instance().GetWindow().Initialize(1920, 1080, "Zephyr3D");
    if (!ZephyrEngine::Instance().GetWindow()) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window\n";
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(ZephyrEngine::Instance().GetWindow());

    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }

    // Set callbacks
    glfwSetFramebufferSizeCallback(ZephyrEngine::Instance().GetWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(ZephyrEngine::Instance().GetWindow(), mouse_callback);
    glfwSetScrollCallback(ZephyrEngine::Instance().GetWindow(), scroll_callback);

    glfwSetInputMode(ZephyrEngine::Instance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    glfwSetWindowShouldClose(ZephyrEngine::Instance().GetWindow(), true);
    glfwTerminate();
}

zephyr::Time& zephyr::ZephyrEngine::GetTime() {
    return m_Time;
}

zephyr::Input& zephyr::ZephyrEngine::GetInput() {
    return m_Input;
}

zephyr::Window& zephyr::ZephyrEngine::GetWindow() {
    return m_Window;
}

zephyr::rendering::IDrawManager& zephyr::ZephyrEngine::Drawing() {
    return m_CurrentScene->GetDrawManager();
}

zephyr::physics::IPhysicsManager& zephyr::ZephyrEngine::Physics() {
    return m_CurrentScene->GetPhysicsManager();
}

zephyr::resources::ResourcesManager& zephyr::ZephyrEngine::Resources() {
    return m_CurrentScene->GetResourcesManager();
}
