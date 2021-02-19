#include "SpotLight.h"

#include "../Object.h"
#include "../../Scene.h"

zephyr::cbs::SpotLight::SpotLight(class Object& object, ID_t id, float CutOff, float OutterCutOff, float Constant, float Linear, float Quadratic, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
    : Component(object, id)
    , m_SpotLight(static_cast<rendering::Phong*>(Object().Scene().Rendering().Shader("Phong"))->CreateSpotLight()) {

    if (m_SpotLight) {
        m_SpotLight->CutOff = CutOff;
        m_SpotLight->OutterCutOff = OutterCutOff;
        m_SpotLight->Constant = Constant;
        m_SpotLight->Linear = Linear;
        m_SpotLight->Quadratic = Quadratic;
        m_SpotLight->Ambient = Ambient;
        m_SpotLight->Diffuse = Diffuse;
        m_SpotLight->Specular = Specular;
    }
}

void zephyr::cbs::SpotLight::Initialize() {
    if (m_SpotLight) {
        m_SpotLight->Position = (*TransformIn).GlobalPosition();
        m_SpotLight->Direction = (*TransformIn).Front();
    }
}

void zephyr::cbs::SpotLight::Update() {
    if (m_SpotLight) {
        m_SpotLight->Position = (*TransformIn).GlobalPosition();
        m_SpotLight->Direction = (*TransformIn).Front();
    }
}

void zephyr::cbs::SpotLight::Destroy() {
    static_cast<rendering::Phong*>(Object().Scene().Rendering().Shader("Phong"))->DestroySpotLight(m_SpotLight);
}
