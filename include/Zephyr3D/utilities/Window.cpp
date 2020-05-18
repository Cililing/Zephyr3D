#include "Window.h"
#include "../Engine.h"

void zephyr::Window::Initialize(unsigned int width, unsigned int height, const std::string& title) {
    m_Width = width;
    m_Height = height;
    m_Title = title;

    m_GLFWHandler = glfwCreateWindow(m_Width, m_Height, title.c_str(), nullptr, nullptr);
}

void zephyr::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void*)window;

    zephyr::Engine::Instance().GetWindow().m_Width = width;
    zephyr::Engine::Instance().GetWindow().m_Height = height;
    glViewport(0, 0, width, height);
}
