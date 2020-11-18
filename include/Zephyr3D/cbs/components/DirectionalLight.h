#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Component.h"
#include "../../scenes/Scene.h"
#include "../../rendering/IShaderProperty.h"

namespace zephyr::cbs {

class DirectionalLight : public Component, public zephyr::rendering::IShaderProperty {
public:
    DirectionalLight(class Object& object, ID_t id, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void Initialize() override;
    void Destroy() override;

    void SetProperty(const zephyr::rendering::ShaderProgram& shader) const override;

private:
    glm::vec3 m_Direction;
    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
};

}

#endif
