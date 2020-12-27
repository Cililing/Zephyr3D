#ifndef IDrawable_h
#define IDrawable_h

#include "ShaderProgram.h"

namespace zephyr::rendering {

class IDrawable {
public:
    IDrawable() = default;
    IDrawable(const IDrawable&) = delete;
    IDrawable& operator=(const IDrawable&) = delete;
    IDrawable(IDrawable&&) = delete;
    IDrawable& operator=(IDrawable&&) = delete;
    virtual ~IDrawable() = default;

    virtual void Draw(const ShaderProgram &shader) const = 0;

    void UserPointer(void* user_pointer) { m_UserPointer = user_pointer; }
    void* UserPointer() const { return m_UserPointer; }

private:
    void* m_UserPointer;
};

}

#endif