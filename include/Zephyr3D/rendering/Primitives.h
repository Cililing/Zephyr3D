#ifndef Primitives_h
#define Primitives_h

#include "IDrawable.h"

namespace zephyr::rendering {

class Line {
public:
    Line() {
        GLfloat vertices[] = {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~Line() {
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    Line(const Line&) = delete;
    Line& operator=(const Line&) = delete;
    Line(Line&&) = delete;
    Line& operator=(Line&&) = delete;

    GLuint VBO() const { return m_VBO; }
    GLuint VAO() const { return m_VAO; }

    glm::vec3 End() const { return glm::vec3(1.0f, 0.0f, 0.0f); }

    void Draw() const {
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
    }

    void DrawInstances(GLuint instance_count) const {
        glBindVertexArray(m_VAO);
        glDrawArraysInstanced(GL_LINES, 0, 2, instance_count);
        glBindVertexArray(0);
    }

private:
    GLuint m_VBO;
    GLuint m_VAO;
};


class Triangle {
    const float X_VAL = std::sqrt(3) / 2;

public:
    // Creates isosceles triangle of which distances between vertices and origin are equal 1
    Triangle() {
        GLfloat vertices[] = {
             0.0f,  1.0f,  0.0f,    // Upper
            -X_VAL, -0.5f, 0.0f,    // Lower left
             X_VAL, -0.5f, 0.0f     // Lower right
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~Triangle() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;
    Triangle(Triangle&&) = delete;
    Triangle& operator=(Triangle&&) = delete;

    glm::vec3 UpperVertex() const { return glm::vec3(0.0f, 1.0f, 0.0f); }
    glm::vec3 LowerLeftVertex() const { return glm::vec3(-X_VAL, -0.5f, 0.0f); }
    glm::vec3 LowerRightVertex() const { return glm::vec3(X_VAL, -0.5f, 0.0f); }

    GLuint VAO() const { return m_VAO; }
    GLuint VBO() const { return m_VBO; }

    void Draw() const {
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    void DrawInstances(GLuint instance_count) const {
        glBindVertexArray(m_VAO);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, instance_count);
        glBindVertexArray(0);
    }

private:
    GLuint m_VAO;
    GLuint m_VBO;
};


class Plane {
public:
    Plane() {
        float vertices[] = {
             0.5f,  0.5f, 0.0f, // top right
             0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f, // top left 
             0.5f,  0.5f, 0.0f  // top right
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~Plane() {
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    Plane(const Plane&) = delete;
    Plane& operator=(const Plane&) = delete;
    Plane(Plane&&) = delete;
    Plane& operator=(Plane&&) = delete;

    glm::vec3 Normal() const { return glm::vec3(0.0f, 0.0f, 1.0f); }

    GLuint VBO() const { return m_VBO; }
    GLuint VAO() const { return m_VAO; }

    void Draw() const {
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 5);
        glBindVertexArray(0);
    }

    void DrawInstances(GLuint instance_count) const {
        glBindVertexArray(m_VAO);
        glDrawArraysInstanced(GL_LINE_STRIP, 0, 5, instance_count);
        glBindVertexArray(0);
    }

private:
    GLuint m_VBO;
    GLuint m_VAO;
};


class Cuboid {
public:
    Cuboid() {
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~Cuboid() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    Cuboid(const Cuboid&) = delete;
    Cuboid& operator=(const Cuboid&) = delete;
    Cuboid(Cuboid&&) = delete;
    Cuboid& operator=(Cuboid&&) = delete;

    GLuint VBO() const { return m_VBO; }
    GLuint VAO() const { return m_VAO; }

    void Draw() const {
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 17);
        glBindVertexArray(0);
    }

    void DrawInstances(GLuint instance_count) const {
        glBindVertexArray(m_VAO);
        glDrawArraysInstanced(GL_LINE_STRIP, 0, 17, instance_count);
        glBindVertexArray(0);
    }

private:
    GLuint m_VBO;
    GLuint m_VAO;
};

// TODO: 
class Sphere {
public:
    Sphere() {

    }

    ~Sphere() {

    }

    Sphere(const Sphere&) = delete;
    Sphere& operator=(const Sphere&) = delete;
    Sphere(Sphere&&) = delete;
    Sphere& operator=(Sphere&&) = delete;

    GLuint VBO() const { return m_VBO; }
    GLuint VAO() const { return m_VAO; }

    void Draw() {

    }

private:
    GLuint m_VBO;
    GLuint m_VAO;
};

}

#endif
