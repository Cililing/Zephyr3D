#include "PointLight.h"
#include "../Object.h"
#include "../../Scene.h"
#include "../../debuging/Logger.h"

zephyr::cbs::PointLight::PointLight(class Object& object, ID_t id, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : Component(object, id)
    , m_PointLight(static_cast<rendering::Phong*>(Object().Scene().Rendering().Shader("Phong"))->CreatePointLight()) {

    if (m_PointLight) {
        m_PointLight->Constant = constant;
        m_PointLight->Linear = linear;
        m_PointLight->Quadratic = quadratic;
        m_PointLight->Ambient = ambient;
        m_PointLight->Diffuse = diffuse;
        m_PointLight->Specular = specular;
    }
}

void zephyr::cbs::PointLight::Initialize() {
    if (m_PointLight) {
        m_PointLight->Position = (*TransformIn).GlobalPosition();
    }

    RegisterUpdateCall();
}

void zephyr::cbs::PointLight::Update() {
    if (m_PointLight) {
        m_PointLight->Position = (*TransformIn).GlobalPosition();
    }
}

void zephyr::cbs::PointLight::Destroy() {
    static_cast<rendering::Phong*>(Object().Scene().Rendering().Shader("Phong"))->DestroyPointLight(m_PointLight);
}
