#include "Camera.h"

Camera::Camera(class Object& object, ID_t id, float fovy, float aspect, float near, float far)
    : Component(object, id)
    , m_Camera(fovy, aspect, near, far) {

}

void Camera::Initialize() {
    Object().Scene().RegisterCamera(&m_Camera);

    RegisterUpdateCall();
}

void Camera::Update() {
    m_Camera.Update(TransformIn.Value()->Position(),
                    TransformIn.Value()->Front(),
                    TransformIn.Value()->Up());
}
