#include "Camera.h"
#include "../../ZephyrEngine.h"

zephyr::cbs::Camera::Camera(class Object& object, ID_t id, float fovy, float aspect, float near, float far)
    : Component(object, id)
    , m_Camera(fovy, aspect, near, far) {

}

void zephyr::cbs::Camera::Initialize() {
    Object().Scene().GetDrawManager().RegisterCamera(&m_Camera);

    RegisterUpdateCall();
}

void zephyr::cbs::Camera::Update() {
    m_Camera.Update(TransformIn.Value()->Position(),
                    TransformIn.Value()->Front(),
                    TransformIn.Value()->Up());
}
