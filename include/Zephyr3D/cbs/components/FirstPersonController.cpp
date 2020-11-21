#include "FirstPersonController.h"
#include "Transform.h"

zephyr::cbs::FirstPersonController::FirstPersonController(class Object& object, ID_t id, float movement_speed_fast, float movement_speed_slow, float mouse_sensivity)
    : Component(object, id)
    , m_CurrentMovementSpeed(0.0f)
    , m_MovementSpeedFast(movement_speed_fast)
    , m_MovementSpeedSlow(movement_speed_slow)
    , m_MouseSensitivity(mouse_sensivity)
    , m_VerticalRotation(0.0f)
    , m_LastMousePos(0.0f) {}

void zephyr::cbs::FirstPersonController::Initialize() {
    // TODO store original rotation from Transform component
    m_LastMousePos = zephyr::ZephyrEngine::Instance().GetInput().MousePosition();

    RegisterUpdateCall();
}

void zephyr::cbs::FirstPersonController::Update() {
    // Mouse
    float rot_ver = glm::radians(zephyr::ZephyrEngine::Instance().GetInput().MouseOffset().y * m_MouseSensitivity);
    float rot_hor = glm::radians(-zephyr::ZephyrEngine::Instance().GetInput().MouseOffset().x * m_MouseSensitivity);
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
    TransformIn.Value()->Rotate(glm::vec3(0.0f, rot_hor, 0.0f));
    TransformIn.Value()->RotateRelative(glm::vec3(0.0f, 0.0f, rot_ver));

    // Keyboard
    if (zephyr::ZephyrEngine::Instance().GetInput().KeyHold(GLFW_KEY_LEFT_SHIFT) || zephyr::ZephyrEngine::Instance().GetInput().KeyHold(GLFW_KEY_RIGHT_SHIFT)) {
        m_CurrentMovementSpeed = m_MovementSpeedFast;
    } else {
        m_CurrentMovementSpeed = m_MovementSpeedSlow;
    }

    glm::vec3 movement(0.0f);
    if (zephyr::ZephyrEngine::Instance().GetInput().KeyHold(GLFW_KEY_UP)) {
        movement.x = m_CurrentMovementSpeed * zephyr::ZephyrEngine::Instance().GetTime().DeltaTime();;
    }
    if (zephyr::ZephyrEngine::Instance().GetInput().KeyHold(GLFW_KEY_DOWN)) {
        movement.x = -m_CurrentMovementSpeed * zephyr::ZephyrEngine::Instance().GetTime().DeltaTime();;
    }
    if (zephyr::ZephyrEngine::Instance().GetInput().KeyHold(GLFW_KEY_LEFT)) {
        movement.z = -m_CurrentMovementSpeed * zephyr::ZephyrEngine::Instance().GetTime().DeltaTime();;
    }
    if (zephyr::ZephyrEngine::Instance().GetInput().KeyHold(GLFW_KEY_RIGHT)) {
        movement.z = m_CurrentMovementSpeed * zephyr::ZephyrEngine::Instance().GetTime().DeltaTime();;
    }

    TransformIn.Value()->Move(movement);
}
