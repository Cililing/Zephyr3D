#include "Transform.h"

#include "../Object.h"

void Transform::Initialize() {
    UpdateModel();
}

void Transform::Identity() {
    m_Position = glm::vec3(0.0f);
    m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    m_Scale = glm::vec3(1.0f);

    m_Model = glm::mat4(1.0f);
}

glm::mat4 Transform::Model() const {
    if (Parent.Connected()) {
        glm::mat4 model = glm::translate(Parent.Value()->Model(), m_Position) * glm::toMat4(m_Rotation);
        model = glm::scale(model, m_Scale);
        return model;
    } else {
        return m_Model;
    }
}

void Transform::Model(const glm::mat4 model) {
    m_Model = model;
}

void Transform::Model(const float* model) {
    m_Model = glm::make_mat4(model);
}

glm::vec3 Transform::Position() const {
    if (Parent.Connected()) {
        return glm::vec3(Model()[3]);
    } else {
        return m_Position;
    }
}

void Transform::Position(const glm::vec3& position) {
    m_Position = position;

    UpdateModel();
}

void Transform::Move(const glm::vec3& vector) {
    m_Position = m_Position + m_Rotation * vector;

    UpdateModel();
}

glm::quat Transform::Rotation() const {
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

void Transform::Rotation(const glm::quat &rotation) {
    m_Rotation = rotation;

    UpdateModel();
}

void Transform::Rotate(const glm::quat& rotation) {
    m_Rotation = rotation * m_Rotation;

    UpdateModel();
}

void Transform::RotateRelative(const glm::quat& rotation) {
    m_Rotation = m_Rotation * rotation;

    UpdateModel();
}

glm::vec3 Transform::Scale() const {
    if (Parent.Connected()) {
        return m_Scale * Parent.Value()->Scale();
    } else {
        return m_Scale;
    }
}

void Transform::Scale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

void Transform::UpdateModel() {
    if (Parent.Connected()) {
        m_Model = Parent.Value()->Model();
    } else {
        m_Model = glm::mat4(1.0f);
    }

    m_Model = glm::translate(m_Model, m_Position);
    m_Model = m_Model * glm::toMat4(m_Rotation);
    m_Model = glm::scale(m_Model, m_Scale);
}
