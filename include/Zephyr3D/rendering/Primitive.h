#ifndef Primitives_h
#define Primitives_h

#pragma warning(push, 0)
#include <glad/glad.h>

#include <glm/glm.hpp>
#pragma warning(pop)

#include <vector>

namespace zephyr::rendering {

class Primitive {
public:
    explicit Primitive(const std::vector<GLfloat>& vertices, GLenum mode);

    Primitive() = delete;
    Primitive(const Primitive& other);
    Primitive& operator=(const Primitive& other);
    Primitive(Primitive&& other);
    Primitive& operator=(Primitive&& other);

    static Primitive Line();
    static Primitive Triangle();
    static Primitive Plane();
    static Primitive Cube();

    GLuint VAO() const;
    GLuint VBO() const;

    void Draw() const;
    void DrawInstances(GLsizei count) const;

private:
    GLuint m_VAO;
    GLuint m_VBO;
    std::vector<GLfloat> m_Vertices;
    GLenum m_Mode;
    GLsizei m_Count;

    void Generate();
};

}

#endif
