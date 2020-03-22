#include "Cuboid.h"

//A -0.5f, -0.5f, -0.5f, color.x, color.y, color.z,
//B -0.5f, -0.5f,  0.5f, color.x, color.y, color.z,
//C -0.5f,  0.5f, -0.5f, color.x, color.y, color.z,
//D -0.5f,  0.5f,  0.5f, color.x, color.y, color.z,
//E  0.5f, -0.5f, -0.5f, color.x, color.y, color.z,
//F  0.5f, -0.5f,  0.5f, color.x, color.y, color.z,
//G  0.5f,  0.5f, -0.5f, color.x, color.y, color.z,
//H  0.5f,  0.5f,  0.5f, color.x, color.y, color.z,

Cuboid::Cuboid(glm::mat4 model, glm::vec3 color)
    : m_Model(model) {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, color.x, color.y, color.z,
        -0.5f, -0.5f,  0.5f, color.x, color.y, color.z,
        -0.5f,  0.5f,  0.5f, color.x, color.y, color.z,
         0.5f,  0.5f,  0.5f, color.x, color.y, color.z,
         0.5f, -0.5f,  0.5f, color.x, color.y, color.z,
         0.5f, -0.5f,  0.5f, color.x, color.y, color.z,
         0.5f, -0.5f, -0.5f, color.x, color.y, color.z,
         0.5f,  0.5f, -0.5f, color.x, color.y, color.z,
        -0.5f,  0.5f, -0.5f, color.x, color.y, color.z,
        -0.5f,  0.5f,  0.5f, color.x, color.y, color.z,
        -0.5f, -0.5f,  0.5f, color.x, color.y, color.z,
         0.5f, -0.5f,  0.5f, color.x, color.y, color.z,
         0.5f,  0.5f,  0.5f, color.x, color.y, color.z,
         0.5f,  0.5f, -0.5f, color.x, color.y, color.z,
         0.5f, -0.5f, -0.5f, color.x, color.y, color.z,
        -0.5f, -0.5f, -0.5f, color.x, color.y, color.z,
        -0.5f,  0.5f, -0.5f, color.x, color.y, color.z
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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Cuboid::~Cuboid() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void Cuboid::Draw(const ShaderProgram& shader) const {
    shader.Uniform("model", m_Model);

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_LINE_STRIP, 0, 17);
    glBindVertexArray(0);
}
