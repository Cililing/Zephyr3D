#include "FirstPersonController.h"
#include "../Object.h"
#include "../../Scene.h"
#include "../../ZephyrEngine.h"

zephyr::cbs::FirstPersonController::FirstPersonController(class Object& object, ID_t id, float movement_speed_fast, float movement_speed_slow, float mouse_sensivity)
    : Component(object, id)
    , m_MovementSpeedFast(movement_speed_fast)
    , m_MovementSpeedSlow(movement_speed_slow)
    , m_MouseSensitivity(mouse_sensivity) {}

void zephyr::cbs::FirstPersonController::Initialize() {
    assert(TransformIn.Connected());

    // TODO store original rotation from Transform component
    m_LastMousePos = ZephyrEngine::Instance().Input().MousePosition();

    RegisterUpdateCall();
}

void zephyr::cbs::FirstPersonController::Update() {
    // Mouse
    float rot_ver = glm::radians(ZephyrEngine::Instance().Input().MouseOffset().y * m_MouseSensitivity);
    float rot_hor = glm::radians(-ZephyrEngine::Instance().Input().MouseOffset().x * m_MouseSensitivity);
    m_VerticalRotation += rot_ver;

    // Prevent object flip
    if (m_VerticalRotation > DEGREES_60) {
        m_VerticalRotation = DEGREES_60;
        rot_ver = 0.0f;
    } else if (m_VerticalRotation < -DEGREES_60) {
        m_VerticalRotation = -DEGREES_60;
        rot_ver = 0.0f;
    }

    // Update vectors
    TransformIn.Value()->RotateGlobally(glm::vec3(0.0f, rot_hor, 0.0f));
    TransformIn.Value()->RotateLocally(glm::vec3(0.0f, 0.0f, rot_ver));

    // Keyboard
    if (ZephyrEngine::Instance().Input().KeyHold(GLFW_KEY_LEFT_SHIFT) || ZephyrEngine::Instance().Input().KeyHold(GLFW_KEY_RIGHT_SHIFT)) {
        m_CurrentMovementSpeed = m_MovementSpeedFast;
    } else {
        m_CurrentMovementSpeed = m_MovementSpeedSlow;
    }


    glm::vec3 movement(0.0f);
    if (ZephyrEngine::Instance().Input().KeyHold(GLFW_KEY_UP)) {
        movement.x = m_CurrentMovementSpeed;
    }
    if (ZephyrEngine::Instance().Input().KeyHold(GLFW_KEY_DOWN)) {
        movement.x = -m_CurrentMovementSpeed;
    }
    if (ZephyrEngine::Instance().Input().KeyHold(GLFW_KEY_LEFT)) {
        movement.z = -m_CurrentMovementSpeed;
    }
    if (ZephyrEngine::Instance().Input().KeyHold(GLFW_KEY_RIGHT)) {
        movement.z = m_CurrentMovementSpeed;
    }

    TransformIn.Value()->Move(movement);
}
