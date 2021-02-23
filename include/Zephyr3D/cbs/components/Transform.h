#ifndef Transform_h
#define Transform_h

#include "Component.h"
#include "../connections/PropertyOut.h"
#include "../connections/PropertyIn.h"

#pragma warning(push, 0)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#pragma warning(pop)

namespace zephyr::cbs {

class Transform : public Component {
public:
    Transform(class Object& object, ID_t id);

    void Initialize() override;

    void Identity();

    glm::mat4 Model() const;
    void Model(const glm::mat4& model);
    void GlobalModel(const glm::mat4& model);

    glm::vec3 LocalPosition() const;
    void LocalPosition(const glm::vec3& position);
    glm::vec3 GlobalPosition() const;
    void GlobalPosition(const glm::vec3& position);

    glm::quat LocalRotation() const;
    void LocalRotation(const glm::quat& rotation);
    glm::quat GlobalRotation() const;
    void GlobalRotation(const glm::quat& rotation);

    glm::vec3 LocalScale() const;
    void LocalScale(const glm::vec3& scale);
    glm::vec3 GlobalScale() const;
    void GlobalScale(const glm::vec3& scale);

    void Move(const glm::vec3& vector);
    void RotateGlobally(const glm::quat& rotation);
    void RotateLocally(const glm::quat& rotation);

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

}

#endif
