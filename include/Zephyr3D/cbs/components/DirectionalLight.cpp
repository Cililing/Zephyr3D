#include "DirectionalLight.h"
#include "../../Scene.h"

zephyr::cbs::DirectionalLight::DirectionalLight(class Object& object, ID_t id, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : Component(object, id)
    , m_DirectionalLight(static_cast<rendering::Phong*>(Object().Scene().Rendering().Shader("Phong"))->CreateDirectionalLight()) {
    if (m_DirectionalLight) {
        m_DirectionalLight->Ambient = ambient;
        m_DirectionalLight->Diffuse = diffuse;
        m_DirectionalLight->Specular = specular;
    }
}

void zephyr::cbs::DirectionalLight::Initialize() {
    if (m_DirectionalLight) {
        m_DirectionalLight->Direction = (*TransformIn).Front();
    }
}

void zephyr::cbs::DirectionalLight::Update() {
    if (m_DirectionalLight) {
        m_DirectionalLight->Direction = (*TransformIn).Front();
    }
}

void zephyr::cbs::DirectionalLight::Destroy() {
    static_cast<rendering::Phong*>(Object().Scene().Rendering().Shader("Phong"))->DestroyDirectionalLight();
}
