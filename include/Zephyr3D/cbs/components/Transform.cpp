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

void zephyr::cbs::Transform::Model(const glm::mat4& model) {
    m_Model = model;
}

void zephyr::cbs::Transform::GlobalModel(const glm::mat4& model) {
    if (Parent.Connected()) {
        m_Model = glm::inverse(Parent.Value()->Model()) * model;
    } else {
        m_Model = model;
    }
}

void zephyr::cbs::Transform::LocalPosition(const glm::vec3& position) {
    m_Position = position;

    UpdateModel();
}

glm::vec3 zephyr::cbs::Transform::LocalPosition() const {
    return m_Position;
}

void zephyr::cbs::Transform::GlobalPosition(const glm::vec3& position) {
    if (Parent.Connected()) {
        m_Position = position - Parent.Value()->GlobalPosition();
    } else {
        m_Position = position;
    }

    UpdateModel();
}

glm::vec3 zephyr::cbs::Transform::GlobalPosition() const {
    return glm::vec3(Model()[3]);
}

glm::quat zephyr::cbs::Transform::LocalRotation() const {
    return m_Rotation;
}

void zephyr::cbs::Transform::LocalRotation(const glm::quat &rotation) {
    m_Rotation = rotation;

    UpdateModel();
}

glm::quat zephyr::cbs::Transform::GlobalRotation() const {
    glm::quat rotation;
    glm::vec3 scale, translation, skew;
    glm::vec4 perspective;
    glm::decompose(Model(), scale, rotation, translation, skew, perspective);

    return rotation;
}

void zephyr::cbs::Transform::GlobalRotation(const glm::quat& rotation) {
    // TODO
    static_assert(true);
}

glm::vec3 zephyr::cbs::Transform::LocalScale() const {
    return m_Scale;
}

void zephyr::cbs::Transform::LocalScale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

glm::vec3 zephyr::cbs::Transform::GlobalScale() const {
    glm::quat rotation;
    glm::vec3 scale, translation, skew;
    glm::vec4 perspective;
    glm::decompose(Model(), scale, rotation, translation, skew, perspective);

    return scale;
}

void zephyr::cbs::Transform::GlobalScale(const glm::vec3& scale) {
    if (Parent.Connected()) {
        m_Scale = scale - Parent.Value()->GlobalScale();
    }
    else {
        m_Scale = scale;
    }

    UpdateModel();
}

void zephyr::cbs::Transform::Move(const glm::vec3& vector) {
    m_Position = m_Position + m_Rotation * vector;

    UpdateModel();
}

void zephyr::cbs::Transform::RotateGlobally(const glm::quat& rotation) {
    m_Rotation = rotation * m_Rotation;

    UpdateModel();
}

void zephyr::cbs::Transform::RotateLocally(const glm::quat& rotation) {
    m_Rotation = m_Rotation * rotation;

    UpdateModel();
}

void zephyr::cbs::Transform::UpdateModel() {
    m_Model = glm::translate(glm::mat4(1.0f), m_Position);
    m_Model = m_Model * glm::toMat4(m_Rotation);
    m_Model = glm::scale(m_Model, m_Scale);
}
