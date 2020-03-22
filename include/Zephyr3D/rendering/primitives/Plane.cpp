#include "Plane.h"

Plane::Plane(glm::mat4 model, glm::vec3 color)
    : m_Model(model) {
    float vertices[] = {
         0.5f,  0.5f, 0.0f, color.x, color.y, color.z, // top right
         0.5f, -0.5f, 0.0f, color.x, color.y, color.z, // bottom right
        -0.5f, -0.5f, 0.0f, color.x, color.y, color.z, // bottom left
        -0.5f,  0.5f, 0.0f, color.x, color.y, color.z, // top left 
         0.5f,  0.5f, 0.0f, color.x, color.y, color.z  // top right
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

Plane::~Plane() {
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Plane::Draw(const ShaderProgram& shader) const {
    shader.Uniform("model", m_Model);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_LINE_STRIP, 0, 5);
    glBindVertexArray(0);
}
