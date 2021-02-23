#ifndef FirstPersonController_h
#define FirstPersonController_h

#include "Component.h"
#include "Transform.h"
#include "../connections/PropertyIn.h"

#pragma warning(push, 0)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#pragma warning(pop)

#include <iostream>

namespace zephyr::cbs {

constexpr auto DEGREES_60 = (90.0f * 3.14f / 180.0f);

class FirstPersonController : public Component {
public:
    FirstPersonController(class Object& object, ID_t id, float movement_speed_fast, float movement_speed_slow, float mouse_sensitivity);

    void Initialize() override;
    void Update() override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    float m_CurrentMovementSpeed{ 0.0f };
    float m_MovementSpeedFast;
    float m_MovementSpeedSlow;
    float m_MouseSensitivity;
    float m_VerticalRotation{ 0.0f };
    glm::vec2 m_LastMousePos{ 0.0f };
};

}

#endif