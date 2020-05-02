#ifndef Cubemap_h
#define Cubemap_h

#include "IDrawable.h"

#pragma warning(push, 0)
#include <stb_image.h>
#pragma warning(pop)

#include <iostream>
#include <string>

namespace zephyr::resources { class Image; }

namespace zephyr::rendering {

class Cubemap : public IDrawable {
public:
    Cubemap(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    Cubemap(const resources::Image& right, const resources::Image& left, const resources::Image& top, const resources::Image& bottom, const resources::Image& back, const resources::Image& front);

    void Draw(const ShaderProgram& shader) const override;

private:
    unsigned int m_ID;
    unsigned int m_VAO;
    unsigned int m_VBO;

    void m_Load(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    void m_Initialize();
};

}

#endif
