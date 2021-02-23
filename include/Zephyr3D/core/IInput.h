#ifndef IInput_hh
#define IInput_h

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning(pop)


namespace zephyr {

class IInput {
public:
    enum class EKeyState {
        FREE = 0,   // The key is not being pressed nor has been
        PRESSED,    // The key is pressed in this frame
        HOLD,       // The key is still being pressed
        RELEASED,   // The key was pressed in previous frame and is not now
    };

    IInput() = default;
    IInput(const IInput&) = delete;
    IInput& operator=(const IInput&) = delete;
    IInput(IInput&&) = delete;
    IInput& operator=(IInput&&) = delete;
    virtual ~IInput() = default;

    virtual bool AnyKeyPressed() const = 0;
    virtual bool AnyKeyHold() const = 0;
    virtual bool AnyKeyReleased() const = 0;
    virtual bool KeyPressed(int glfw_key_enum) const = 0;
    virtual bool KeyHold(int glfw_key_enum) const = 0;
    virtual bool KeyReleased(int glfw_key_enum) const = 0;
    virtual IInput::EKeyState KeyState(int glfw_key_enum) const = 0;
    virtual const glm::vec2& MousePosition() const = 0;
    virtual const glm::vec2& MouseOffset() const = 0;
    virtual float ScrollOffset() const = 0;
};

}

#endif
