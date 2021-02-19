#ifndef Camera_h
#define Camera_h

#include "Component.h"
#include "Transform.h"
#include "../connections/PropertyIn.h"
#include "../../rendering/PerspectiveCamera.h"

namespace zephyr::cbs {

class Camera : public Component {
public:
    Camera(class Object& object, ID_t id, float fovy, float aspect, float near, float far);

    void Initialize() override;
    void Update() override;

    PropertyIn<Transform*> TransformIn { this };

private:
    rendering::PerspectiveCamera m_Camera;
};

}

#endif
