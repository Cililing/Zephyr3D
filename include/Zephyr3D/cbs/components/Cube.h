#ifndef Cube_h
#define Cube_h

#include "Component.h"
#include "../Object.h"
#include "../../scenes/Scene.h"
#include "../connections/PropertyIn.h"
#include "../../rendering/IDrawable.h"

namespace zephyr::cbs {

class Cube : public Component, public zephyr::rendering::IDrawable {
public:
    Cube(class Object& object, ID_t id, const glm::vec3& color);

    void Draw(const zephyr::rendering::ShaderProgram& shader) const override;

    void Initialize() override;
    void Destroy() override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    GLuint m_VBO;
    GLuint m_VAO;
};

}

#endif
