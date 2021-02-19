#ifndef ThirdPersonController_h
#define ThirdPersonController_h

#include "Component.h"
#include "Transform.h"
#include "../connections/PropertyIn.h"

#pragma warning(push, 0)
#include <glm/gtx/rotate_vector.hpp>
#pragma warning(pop)

namespace zephyr::cbs {

constexpr auto ROTATION_LIMIT = (75.0f * 3.14f / 180.0f);

class ThirdPersonController : public Component {
public:
    ThirdPersonController(class Object& object, ID_t id, class Object& target, glm::vec3 front, glm::vec3 right, float radius, float mouse_sensitivity);
    
    void Initialize() override;
    void Update() override;
    
    void Radius(float radius);
    float Radius() const  { return m_Radius; }

    PropertyIn<Transform*> TransformIn{ this };

private:
    class Object& m_Target;
    Transform* m_TargetTransform{ nullptr };
    float m_Radius;
    float m_MouseSensitivity;
    
    glm::vec3 m_Front;
    glm::vec3 m_RotationAxis;
    float m_XRotation{ 0.0f };
    float m_YRotation{ 0.0f };
    
    glm::quat m_RotationBeetwen(const glm::vec3& start, const glm::vec3& dest);
};

}

#endif
