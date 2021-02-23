#ifndef PointLight_hpp
#define PointLight_hpp

#include "Component.h"
#include "Transform.h"
#include "../connections/PropertyIn.h"
#include "../../rendering/shaders/Phong.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace zephyr::cbs {

class PointLight : public Component {
public:
    PointLight(class Object& object, ID_t id, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void Initialize() override;
    void Update() override;
    void Destroy() override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    rendering::Phong::PointLight* m_PointLight;
};

}

#endif
