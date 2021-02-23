#include "Clock.h"

void zephyr::Clock::Initialize() {
    m_CurrentTime = static_cast<float>(glfwGetTime());
}

void zephyr::Clock::HoldFrame() {
    m_CurrentTime = static_cast<float>(glfwGetTime());
    m_DeltaTime = m_CurrentTime - m_LastFrame;
}

void zephyr::Clock::Update() {
    m_LastFrame = m_CurrentTime;
    m_CurrentTime = static_cast<float>(glfwGetTime());
    m_DeltaTime = m_CurrentTime - m_LastFrame;
}

float zephyr::Clock::CurrentTime() const {
    return m_CurrentTime;
}

float zephyr::Clock::DeltaTime() const {
    return m_DeltaTime;
}
