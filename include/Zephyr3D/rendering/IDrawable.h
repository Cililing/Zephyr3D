#ifndef IDrawable_h
#define IDrawable_h

#include "ShaderProgram.h"

class IDrawable {
public:
    IDrawable() = default;
    IDrawable(const IDrawable&) = delete;
    IDrawable& operator=(const IDrawable&) = delete;
    IDrawable(IDrawable&&) = delete;
    IDrawable& operator=(IDrawable&&) = delete;
    virtual ~IDrawable() = default;

    virtual void Draw(const ShaderProgram &shader) const = 0;
};

#endif