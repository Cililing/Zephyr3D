#include "DirectionalLight.h"

zephyr::cbs::DirectionalLight::DirectionalLight(class Object& object, ID_t id, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : Component(object, id)
    , m_Direction(direction)
    , m_Ambient(ambient)
    , m_Diffuse(diffuse) 
    , m_Specular(specular) {
}

void zephyr::cbs::DirectionalLight::Initialize() {
    static_cast<rendering::Phong*>(Object().Scene().GetDrawManager().Shader("Phong"))->SetDirectionalLight(m_Direction, m_Ambient, m_Diffuse, m_Specular);
}
