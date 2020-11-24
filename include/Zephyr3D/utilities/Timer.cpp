#include "Timer.h"

zephyr::Timer::Timer()
    : m_CurrentTime(0.0f)
    , m_DeltaTime(0.0f)
    , m_LastFrame(0.0f){
}

void zephyr::Timer::Initialize() {
    m_CurrentTime = static_cast<float>(glfwGetTime());
}

void zephyr::Timer::HoldFrame() {
    m_DeltaTime = static_cast<float>(glfwGetTime()) - m_LastFrame;
}

void zephyr::Timer::Update() {
    m_DeltaTime = static_cast<float>(glfwGetTime()) - m_LastFrame;
    m_LastFrame = CurrentTime();
}
