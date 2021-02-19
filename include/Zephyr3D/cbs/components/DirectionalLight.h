#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Component.h"
#include "Transform.h"
#include "../connections/PropertyIn.h"
#include "../../rendering/shaders/Phong.h"

namespace zephyr::cbs {

class DirectionalLight : public Component {
public:
    DirectionalLight(class Object& object, ID_t id, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void Initialize() override;
    void Update() override;
    void Destroy() override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    rendering::Phong::DirectionalLight* m_DirectionalLight;
};

}

#endif
