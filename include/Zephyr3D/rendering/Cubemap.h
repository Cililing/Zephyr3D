#ifndef Cubemap_h
#define Cubemap_h

#include "IDrawable.h"
#include "../resources/RawTexture.h"

#pragma warning(push, 0)
#include <stb_image.h>
#pragma warning(pop)

#include <iostream>
#include <string>

namespace zephyr::rendering {

class Cubemap : public IDrawable {
public:
    Cubemap(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    Cubemap(const resources::RawTexture& right, const resources::RawTexture& left, const resources::RawTexture& top, const resources::RawTexture& bottom, const resources::RawTexture& back, const resources::RawTexture& front);

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
