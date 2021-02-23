#include "Input.h"
#include "WindowManager.h"
#include "../ZephyrEngine.h"

#pragma warning(disable: 26495)
zephyr::InputManager::InputManager()
    : m_AnyKeyPressed(false)
    , m_AnyKeyHold(false)
    , m_AnyKeyReleased(false)
    , m_MouseFirstMove(true)
    , m_ScrollChanged(true)
    , m_ScrollOffset(0.0f)
    , m_MousePosition(0.0f, 0.0f)
    , m_MouseLastPosition(m_MousePosition)
    , m_MouseOffset(0.0f) {
    
    for (int i = 0; i < GLFW_KEY_MENU + 1; ++i) {
        m_Keys[i] = EKeyState::FREE;
    }
}
#pragma warning(default: 26495)

void zephyr::InputManager::Initialize() {
    GLFWwindow* context = glfwGetCurrentContext();

    glfwSetKeyCallback(context, key_callback);
    glfwSetCursorPosCallback(context, mouse_callback);
    glfwSetScrollCallback(context, scroll_callback);
    glfwSetInputMode(context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void zephyr::InputManager::Update(GLFWwindow *window) {
    m_AnyKeyPressed = false;
    m_AnyKeyHold = false;
    m_AnyKeyReleased = false;

    // Mouse buttons
    for (int i = 0; i < GLFW_MOUSE_BUTTON_8; ++i) {
        if (glfwGetMouseButton(window, i) == GLFW_PRESS) {
            if (m_Keys[i] == EKeyState::FREE || m_Keys[i] == EKeyState::RELEASED) {
                m_Keys[i] = EKeyState::PRESSED;
                m_AnyKeyPressed = true;
            } else if (m_Keys[i] == EKeyState::PRESSED) {
                m_Keys[i] = EKeyState::HOLD;
                m_AnyKeyHold = true;
            }
        } else {
            if (m_Keys[i] == EKeyState::PRESSED || m_Keys[i] == EKeyState::HOLD) {
                m_Keys[i] = EKeyState::RELEASED;
                m_AnyKeyReleased = true;
            } else {
                m_Keys[i] = EKeyState::FREE;
            }
        }
    }

    // Keyboard buttons
    for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_MENU + 1; ++i) {
        if (glfwGetKey(window, i) == GLFW_PRESS) {
            if (m_Keys[i] == EKeyState::FREE || m_Keys[i] == EKeyState::RELEASED) {
                m_Keys[i] = EKeyState::PRESSED;
                m_AnyKeyPressed = true;
            } else if (m_Keys[i] == EKeyState::PRESSED) {
                m_Keys[i] = EKeyState::HOLD;
                m_AnyKeyHold = true;
            }
        } else {
            if (m_Keys[i] == EKeyState::PRESSED || m_Keys[i] == EKeyState::HOLD) {
                m_Keys[i] = EKeyState::RELEASED;
                m_AnyKeyReleased = true;
            } else {
                m_Keys[i] = EKeyState::FREE;
            }
        }
    }

    // Mouse position
    m_MouseOffset.x = m_MousePosition.x - m_MouseLastPosition.x;
    m_MouseOffset.y = m_MouseLastPosition.y - m_MousePosition.y;
    m_MouseLastPosition = m_MousePosition;

    // Mouse scroll
    if (!m_ScrollChanged) {
        m_ScrollOffset = 0.0f;
    }
    m_ScrollChanged = false;
}

bool zephyr::InputManager::KeyPressed(int glfw_key_enum) const {
    return m_Keys[glfw_key_enum] == EKeyState::PRESSED;
}

bool zephyr::InputManager::KeyHold(int glfw_key_enum) const {
    return m_Keys[glfw_key_enum] == EKeyState::HOLD;
}

bool zephyr::InputManager::KeyReleased(int glfw_key_enum) const {
    return m_Keys[glfw_key_enum] == EKeyState::RELEASED;
}

zephyr::InputManager::EKeyState zephyr::InputManager::KeyState(int glfw_key_enum) const {
    return m_Keys[glfw_key_enum];
}

void zephyr::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void zephyr::mouse_callback(GLFWwindow* window, double x_pos, double y_pos) {
    (void*)window;
    static InputManager& manager = dynamic_cast<InputManager&>(ZephyrEngine::Instance().Input());

    manager.m_MousePosition.x = static_cast<float>(x_pos);
    manager.m_MousePosition.y = static_cast<float>(y_pos);

    // Executed only once at the beginning
    if (manager.m_MouseFirstMove) {
        manager.m_MouseLastPosition = manager.m_MousePosition;
        manager.m_MouseFirstMove = false;
    }
}

void zephyr::scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
    (void*)window;
    (void)x_offset;
    static InputManager& manager = dynamic_cast<InputManager&>(ZephyrEngine::Instance().Input());

    manager.m_ScrollOffset = static_cast<float>(y_offset);
    manager.m_ScrollChanged = true;
}
