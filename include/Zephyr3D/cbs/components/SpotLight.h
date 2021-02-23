#ifndef SpotLight_h
#define SpotLight_h

#include "Component.h"
#include "Transform.h"
#include "../connections/PropertyIn.h"
#include "../../rendering/shaders/Phong.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace zephyr::cbs {

class SpotLight : public Component {
public:
    SpotLight(class Object& object, ID_t id, float CutOff, float OutterCutOff, float Constant, float Linear, float Quadratic, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);

    void Initialize() override;
    void Update() override;
    void Destroy() override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    rendering::Phong::SpotLight* m_SpotLight;
};

}

#endif
