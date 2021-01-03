#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Component.h"
#include "../../Scene.h"
#include "../../rendering/shaders/Phong.h"

namespace zephyr::cbs {

class DirectionalLight : public Component {
public:
    DirectionalLight(class Object& object, ID_t id, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void Initialize() override;

private:
    glm::vec3 m_Direction{ 0.0f };
    glm::vec3 m_Ambient{ 0.0f };
    glm::vec3 m_Diffuse{ 0.0f };
    glm::vec3 m_Specular{ 0.0f };
};

}

#endif
