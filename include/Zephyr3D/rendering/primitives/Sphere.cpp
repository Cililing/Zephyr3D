#include "Sphere.h"
#include "SphereData.h"

zephyr::rendering::Sphere::Sphere(glm::mat4 model, glm::vec3 color)
    : m_Model(model) {
    

}

zephyr::rendering::Sphere::~Sphere() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void zephyr::rendering::Sphere::Draw(const ShaderProgram& shader) const {

}
