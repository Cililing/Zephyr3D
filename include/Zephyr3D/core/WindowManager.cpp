#include "WindowManager.h"
#include "../ZephyrEngine.h"

void zephyr::WindowManager::Initialize(unsigned int width, unsigned int height, const std::string& title) {
    m_Width = width;
    m_Height = height;
    m_Title = title;

    m_GLFWHandler = glfwCreateWindow(m_Width, m_Height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_GLFWHandler);

    glfwSetWindowUserPointer(m_GLFWHandler, this);
    glfwSetFramebufferSizeCallback(m_GLFWHandler, framebuffer_size_callback);
}

bool zephyr::WindowManager::ShouldClose() const {
    return glfwWindowShouldClose(m_GLFWHandler);
}

void zephyr::WindowManager::Title(const std::string& title) {
    m_Title = title;
    glfwSetWindowTitle(m_GLFWHandler, m_Title.c_str());
}

void zephyr::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void*)window;

    WindowManager* manager = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
    manager->m_Width = width;
    manager->m_Height = height;
    glViewport(0, 0, width, height);
}
