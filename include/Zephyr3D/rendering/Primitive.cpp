#include "Primitive.h"

zephyr::rendering::Primitive::Primitive(const std::vector<GLfloat>& vertices, GLenum mode) 
    : m_Vertices(vertices)
    , m_Mode(mode)
    , m_Count(static_cast<GLsizei>(m_Vertices.size()) / 3) {
    Generate();
}

zephyr::rendering::Primitive::Primitive(const Primitive& other) 
    : m_Vertices(other.m_Vertices)
    , m_Mode(other.m_Mode)
    , m_Count(other.m_Count) {
    Generate();
}

zephyr::rendering::Primitive& zephyr::rendering::Primitive::operator=(const Primitive& other) {
    m_Vertices = other.m_Vertices;
    m_Mode = other.m_Mode;
    m_Count = other.m_Count;
    Generate();

    return *this;
}

zephyr::rendering::Primitive::Primitive(Primitive&& other) 
    : m_VAO(std::exchange(other.m_VAO, 0))
    , m_VBO(std::exchange(other.m_VBO, 0))
    , m_Vertices(std::move(other.m_Vertices))
    , m_Mode(other.m_Mode)
    , m_Count(other.m_Count) {
}

zephyr::rendering::Primitive& zephyr::rendering::Primitive::operator=(Primitive&& other) {
    if (this == &other)
        return *this;

    m_VAO = std::exchange(other.m_VAO, 0);
    m_VBO = std::exchange(other.m_VBO, 0);
    m_Vertices = std::move(other.m_Vertices);
    m_Mode = other.m_Mode;
    m_Count = other.m_Count;

    return *this;
}

zephyr::rendering::Primitive zephyr::rendering::Primitive::Line() {
    return Primitive(
        std::vector<GLfloat>({0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}), 
        GL_LINES
    );
}

zephyr::rendering::Primitive zephyr::rendering::Primitive::Triangle() {
    static const float X_VAL = std::sqrt(3.0f) / 2.0f;

    return Primitive(
        std::vector<GLfloat>({
             0.0f,  1.0f,  0.0f,    // Upper
            -X_VAL, -0.5f, 0.0f,    // Lower left
             X_VAL, -0.5f, 0.0f     // Lower right
        }),
        GL_TRIANGLES
    );
}

zephyr::rendering::Primitive zephyr::rendering::Primitive::Plane() {
    return Primitive(
        std::vector<GLfloat>({
             0.5f,  0.5f,  0.0f, // top right
             0.5f, -0.5f,  0.0f, // bottom right
            -0.5f, -0.5f,  0.0f, // bottom left
            -0.5f,  0.5f,  0.0f, // top left 
             0.5f,  0.5f,  0.0f  // top right
        }),
        GL_LINE_STRIP
    );
}

zephyr::rendering::Primitive zephyr::rendering::Primitive::Cube() {
    return Primitive(
        std::vector<GLfloat>({
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
        }),
        GL_LINE_STRIP
    );
}

GLuint zephyr::rendering::Primitive::VAO() const {
    return m_VAO;
}

GLuint zephyr::rendering::Primitive::VBO() const {
    return m_VBO;
}

void zephyr::rendering::Primitive::Draw() const {
    glBindVertexArray(m_VAO);
    glDrawArrays(m_Mode, 0, m_Count);
    glBindVertexArray(0);
}

void zephyr::rendering::Primitive::DrawInstances(GLsizei count) const {
    glBindVertexArray(m_VAO);
    glDrawArraysInstanced(m_Mode, 0, m_Count, count);
    glBindVertexArray(0);
}

void zephyr::rendering::Primitive::Generate() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(GLfloat), &m_Vertices[0], GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
