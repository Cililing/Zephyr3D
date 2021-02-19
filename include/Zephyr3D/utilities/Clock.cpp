#include "Clock.h"

zephyr::Clock::Clock()
    : m_CurrentTime(0.0f)
    , m_DeltaTime(0.0f)
    , m_LastFrame(0.0f){
}

void zephyr::Clock::Initialize() {
    m_CurrentTime = static_cast<float>(glfwGetTime());
}

void zephyr::Clock::HoldFrame() {
    m_DeltaTime = static_cast<float>(glfwGetTime()) - m_LastFrame;
}

void zephyr::Clock::Update() {
    m_DeltaTime = static_cast<float>(glfwGetTime()) - m_LastFrame;
    m_LastFrame = CurrentTime();
}
