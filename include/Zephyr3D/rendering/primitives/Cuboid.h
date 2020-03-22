#ifndef Cuboid_h
#define Cuboid_h

#include "../IDrawable.h"

class Cuboid : public IDrawable {
public:
    Cuboid(glm::mat4 model, glm::vec3 color);

    Cuboid() = delete;
    Cuboid(const Cuboid&) = delete;
    Cuboid& operator=(const Cuboid&) = delete;
    Cuboid(Cuboid&&) = delete;
    Cuboid& operator=(Cuboid&&) = delete;
    ~Cuboid();

    void Draw(const ShaderProgram& shader) const override;

private:
    GLuint m_VBO;
    GLuint m_VAO;
    glm::mat4 m_Model;
};

#endif
