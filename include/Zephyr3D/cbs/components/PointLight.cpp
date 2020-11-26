#include "PointLight.h"

int zephyr::cbs::PointLight::QUANTITY = 0;

zephyr::cbs::PointLight::PointLight(class Object& object, ID_t id, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
    : Component(object, id)
    , m_Ambient(ambient)
    , m_Diffuse(diffuse)
    , m_Specular(specular)
    , m_Constant(constant)
    , m_Linear(linear)
    , m_Quadratic(quadratic) {

    assert(constant > 0.0f);
    assert(linear > 0.0f);
    assert(quadratic > 0.0f);

    m_Index = QUANTITY;
    QUANTITY = (QUANTITY + 1) % 4;
}

void zephyr::cbs::PointLight::Initialize() {
    Object().Scene().GetDrawManager().RegisterShaderProperty(this, "Phong");
}

void zephyr::cbs::PointLight::Destroy() {
    Object().Scene().GetDrawManager().UnregisterShaderProperty(this, "Phong");
}

void zephyr::cbs::PointLight::SetProperty(const rendering::ShaderProgram& shader) const {
    std::string pointLight = "pointLights[" + std::to_string(m_Index) + "].";

    shader.Uniform(pointLight + "position", Object().Root().Position());
    shader.Uniform(pointLight + "ambient", m_Ambient);
    shader.Uniform(pointLight + "diffuse", m_Diffuse);
    shader.Uniform(pointLight + "constant", m_Constant);
    shader.Uniform(pointLight + "linear", m_Linear);
    shader.Uniform(pointLight + "quadratic", m_Quadratic);
}

void zephyr::cbs::PointLight::Ambient(const glm::vec3& ambient) {
    m_Ambient = ambient;

    NumberInRange(m_Ambient.x);
    NumberInRange(m_Ambient.y);
    NumberInRange(m_Ambient.z);
}

void zephyr::cbs::PointLight::Diffuse(const glm::vec3& diffuse) {
    m_Diffuse = diffuse;

    NumberInRange(m_Diffuse.x);
    NumberInRange(m_Diffuse.y);
    NumberInRange(m_Diffuse.z);
}

void zephyr::cbs::PointLight::Constant(float constant) {
    if (constant <= 0) {
        constant = 0.0000001f;
    }

    m_Constant = constant;
}

void zephyr::cbs::PointLight::Linear(float linear) {
    if (linear <= 0) {
        linear = 0.0000001f;
    }

    m_Linear = linear;
}

void zephyr::cbs::PointLight::Quadratic(float quadratic) {
    if (quadratic <= 0) {
        quadratic = 0.0000001f;
    }

    m_Quadratic = quadratic;
}
