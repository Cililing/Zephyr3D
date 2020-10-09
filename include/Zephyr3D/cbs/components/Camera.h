#ifndef Camera_h
#define Camera_h

#include "Component.h"
#include "../connections/PropertyIn.h"
#include "../Object.h"
#include "../../scenes/Scene.h"
#include "../../rendering/PerspectiveCamera.h"
#include "../../rendering/OrthographicCamera.h"

#pragma warning(push, 0)
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#pragma warning(pop)

#include <iostream>
#include <string>

#undef far
#undef near

class Camera : public Component {
public:
    Camera(class Object& object, ID_t id, float fovy, float aspect, float near, float far);

    void Initialize() override;
    void Update() override;

    PropertyIn<Transform*> TransformIn { this };

private:
    zephyr::rendering::PerspectiveCamera m_Camera;
};

#endif
