#ifndef Input_hpp
#define Input_hpp

#include "IInput.h"

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

namespace zephyr {

class InputManager : public IInput {
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
    friend void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

public:
    InputManager();

    void Initialize();
    void Update(GLFWwindow *window);

    bool AnyKeyPressed() const { return m_AnyKeyPressed; }
    bool AnyKeyHold() const { return m_AnyKeyHold; }
    bool AnyKeyReleased() const { return m_AnyKeyReleased; }
    bool KeyPressed(int glfw_key_enum) const;
    bool KeyHold(int glfw_key_enum) const ;
    bool KeyReleased(int glfw_key_enum) const ;
    IInput::EKeyState KeyState(int glfw_key_enum) const;

    const glm::vec2& MousePosition() const { return m_MousePosition; }
    const glm::vec2& MouseOffset() const { return m_MouseOffset; }
    float ScrollOffset() const { return m_ScrollOffset; }

private:
    bool m_AnyKeyPressed;
    bool m_AnyKeyHold;
    bool m_AnyKeyReleased;
    IInput::EKeyState m_Keys[GLFW_KEY_MENU + 1];

    bool m_MouseFirstMove;
    bool m_ScrollChanged;
    float m_ScrollOffset;
    glm::vec2 m_MousePosition;
    glm::vec2 m_MouseLastPosition;
    glm::vec2 m_MouseOffset;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void scroll_callback(GLFWwindow* window, double x_pos, double y_pos);

}

#endif
