#include "WindowManager.h"
#include "../ZephyrEngine.h"

void zephyr::WindowManager::Initialize(unsigned int width, unsigned int height, const std::string& title) {
    m_Width = width;
    m_Height = height;
    m_Title = title;

    m_GLFWHandler = glfwCreateWindow(m_Width, m_Height, title.c_str(), nullptr, nullptr);
}

void zephyr::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void*)window;

    zephyr::ZephyrEngine::Instance().GetWindow().m_Width = width;
    zephyr::ZephyrEngine::Instance().GetWindow().m_Height = height;
    glViewport(0, 0, width, height);
}
