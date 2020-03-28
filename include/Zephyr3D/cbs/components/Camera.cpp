#include "Camera.h"

Camera::Camera(float fovy, float aspect, float near, float far) 
    : m_Camera(fovy, aspect, near, far) {

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
