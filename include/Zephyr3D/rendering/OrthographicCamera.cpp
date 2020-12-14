#include "OrthographicCamera.h"

zephyr::rendering::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
    : m_View(0.0f)
    , m_Projection(glm::ortho(left, right, bottom, top, near, far))
    , m_Position(0.0f) {

}

glm::mat4 zephyr::rendering::OrthographicCamera::View() {
    return m_View;
}

glm::mat4 zephyr::rendering::OrthographicCamera::Projection() {
    return m_Projection;
}

glm::vec3 zephyr::rendering::OrthographicCamera::LocalPosition() {
    return m_Position;
}

void zephyr::rendering::OrthographicCamera::Update(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up) {
    m_Position = position;

    m_View = glm::lookAt(m_Position, m_Position + front, up);
}
