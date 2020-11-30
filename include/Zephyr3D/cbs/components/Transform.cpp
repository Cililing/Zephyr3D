#include "Transform.h"

#include "../Object.h"

zephyr::cbs::Transform::Transform(class Object& object, ID_t id)
    : Component(object, id) {

}

void zephyr::cbs::Transform::Initialize() {
    UpdateModel();
}

void zephyr::cbs::Transform::Identity() {
    m_Position = glm::vec3(0.0f);
    m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    m_Scale = glm::vec3(1.0f);

    m_Model = glm::mat4(1.0f);
}

glm::mat4 zephyr::cbs::Transform::Model() const {
    if (Parent.Connected()) {
        return Parent.Value()->Model() * m_Model;
    } else {
        return m_Model;
    }
}

void zephyr::cbs::Transform::Model(const glm::mat4 model) {
    m_Model = model;
}

void zephyr::cbs::Transform::Model(const float* model) {
    m_Model = glm::make_mat4(model);
}

glm::vec3 zephyr::cbs::Transform::Position() const {
    return glm::vec3(Model()[3]);
}

void zephyr::cbs::Transform::Position(const glm::vec3& position) {
    m_Position = position;

    UpdateModel();
}

void zephyr::cbs::Transform::Move(const glm::vec3& vector) {
    m_Position = m_Position + m_Rotation * vector;

    UpdateModel();
}

glm::quat zephyr::cbs::Transform::Rotation() const {
    glm::quat rotation;
    glm::vec3 scale, translation, skew;
    glm::vec4 perspective;
    glm::decompose(Model(), scale, rotation, translation, skew, perspective);

    return rotation;
}

void zephyr::cbs::Transform::Rotation(const glm::quat &rotation) {
    m_Rotation = rotation;

    UpdateModel();
}

void zephyr::cbs::Transform::Rotate(const glm::quat& rotation) {
    m_Rotation = rotation * m_Rotation;

    UpdateModel();
}

void zephyr::cbs::Transform::RotateRelative(const glm::quat& rotation) {
    m_Rotation = m_Rotation * rotation;

    UpdateModel();
}

glm::vec3 zephyr::cbs::Transform::Scale() const {
    glm::quat rotation;
    glm::vec3 scale, translation, skew;
    glm::vec4 perspective;
    glm::decompose(Model(), scale, rotation, translation, skew, perspective);

    return scale;
}

void zephyr::cbs::Transform::Scale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

void zephyr::cbs::Transform::UpdateModel() {
    m_Model = glm::translate(glm::mat4(1.0f), m_Position);
    m_Model = m_Model * glm::toMat4(m_Rotation);
    m_Model = glm::scale(m_Model, m_Scale);
}
