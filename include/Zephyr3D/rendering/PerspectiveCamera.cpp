#include "PerspectiveCamera.h"

zephyr::rendering::PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far)
    : m_View(0.0f)
    , m_Projection(glm::perspective(fovy, aspect, near, far))
    , m_Position(0.0f) {

}

glm::mat4 zephyr::rendering::PerspectiveCamera::View() {
    return m_View;
}

glm::mat4 zephyr::rendering::PerspectiveCamera::Projection() {
    return m_Projection;
}

glm::vec3 zephyr::rendering::PerspectiveCamera::LocalPosition() {
    return m_Position;
}

void zephyr::rendering::PerspectiveCamera::Update(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up) {
    m_Position = position;

    m_View = glm::lookAt(m_Position, m_Position + front, up);
}
