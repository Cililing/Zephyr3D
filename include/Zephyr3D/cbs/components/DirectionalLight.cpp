#include "DirectionalLight.h"

zephyr::cbs::DirectionalLight::DirectionalLight(class Object& object, ID_t id, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : Component(object, id)
    , m_Direction(direction)
    , m_Ambient(ambient)
    , m_Diffuse(diffuse)
    , m_Specular(specular) {
}

void zephyr::cbs::DirectionalLight::Initialize() {
    Object().Scene().GetDrawManager().RegisterShaderProperty(this, "Phong");
}

void zephyr::cbs::DirectionalLight::Destroy() {
    Object().Scene().GetDrawManager().UnregisterShaderProperty(this, "Phong");
}

void zephyr::cbs::DirectionalLight::SetProperty(const rendering::ShaderProgram& shader) const {
    shader.Uniform("dirLight.direction", m_Direction);
    shader.Uniform("dirLight.ambient", m_Ambient);
    shader.Uniform("dirLight.diffuse", m_Diffuse);
    shader.Uniform("dirLight.specular", m_Specular);
}
