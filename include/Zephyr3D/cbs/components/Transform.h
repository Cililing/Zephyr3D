#ifndef Transform_h
#define Transform_h

#include "Component.h"
#include "../connections/PropertyOut.h"
#include "../connections/PropertyIn.h"

#define GLM_ENABLE_EXPERIMENTAL
#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#pragma warning(pop)

class Transform : public Component {
public:
    void Initialize() override;

    void Identity();

    glm::mat4 Model() const;
    void Model(const glm::mat4 model);
    void Model(const float* model);

    glm::vec3 Position() const;
    void Position(const glm::vec3& position);
    void Move(const glm::vec3& vector);

    glm::quat Rotation() const;
    void Rotation(const glm::quat& rotation);
    void Rotate(const glm::quat& rotation);
    void RotateRelative(const glm::quat& rotation);

    glm::vec3 Scale() const;
    void Scale(const glm::vec3& scale);

    glm::vec3 Front() { return m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f); }
    glm::vec3 Up() { return m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f); }
    glm::vec3 Right() { return m_Rotation * glm::vec3(0.0f, 0.0f, 1.0f); }

    PropertyOut<Transform*> This{ this, this };
    PropertyIn<Transform*> Parent{ this };

private:
    void UpdateModel();

    glm::mat4 m_Model{ 1.0f };
    glm::vec3 m_Position{ 0.0f };
    glm::quat m_Rotation{ glm::vec3(0.0f) };
    glm::vec3 m_Scale{ 1.0f };
};

#endif
