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
        glm::mat4 model = glm::translate(Parent.Value()->Model(), m_Position) * glm::toMat4(m_Rotation);
        model = glm::scale(model, m_Scale);
        return model;
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
    if (Parent.Connected()) {
        return glm::vec3(Model()[3]);
    } else {
        return m_Position;
    }
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
    if (Parent.Connected()) {
        glm::quat rotation;
        glm::vec3 tmp1, tmp2, tmp3;
        glm::vec4 tmp4;
        glm::decompose(Model(), tmp1, rotation, tmp2, tmp3, tmp4);

        return rotation;
    } else {
        return m_Rotation;
    }
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
    if (Parent.Connected()) {
        return m_Scale * Parent.Value()->Scale();
    } else {
        return m_Scale;
    }
}

void zephyr::cbs::Transform::Scale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

void zephyr::cbs::Transform::UpdateModel() {
    if (Parent.Connected()) {
        m_Model = Parent.Value()->Model();
    } else {
        m_Model = glm::mat4(1.0f);
    }

    m_Model = glm::translate(m_Model, m_Position);
    m_Model = m_Model * glm::toMat4(m_Rotation);
    m_Model = glm::scale(m_Model, m_Scale);
}
