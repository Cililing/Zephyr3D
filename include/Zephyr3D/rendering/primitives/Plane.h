#ifndef Plane_h
#define Plane_h

#include "../IDrawable.h"

class Plane : public IDrawable {
public:
    Plane(glm::mat4 model, glm::vec3 color);

    Plane() = delete;
    Plane(const Plane&) = delete;
    Plane& operator=(const Plane&) = delete;
    Plane(Plane&&) = delete;
    Plane& operator=(Plane&&) = delete;
    ~Plane();

    void Draw(const ShaderProgram& shader) const override;

private:
    GLuint m_VBO;
    GLuint m_VAO;
    glm::mat4 m_Model;
};

#endif
