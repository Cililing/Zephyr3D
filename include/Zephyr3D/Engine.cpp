#include "Engine.h"
#include "scenes/Scene.h"

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

void zephyr::Engine::StartScene(Scene& scene) {
    scene.Initialize();
    scene.CreateScene();
    scene.Run();
    scene.Destroy();
}

void zephyr::Engine::Destroy() {
    glfwSetWindowShouldClose(Engine::Instance().GetWindow(), true);
    glfwTerminate();
}

zephyr::Time& zephyr::Engine::GetTime() {
    return m_Time;
}

zephyr::Input& zephyr::Engine::GetInput() {
    return m_Input;
}

zephyr::Window& zephyr::Engine::GetWindow() {
    return m_Window;
}
