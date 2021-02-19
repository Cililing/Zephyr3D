#include "Camera.h"
#include "../Object.h"
#include "../../Scene.h"
#include "../../ZephyrEngine.h"

#undef far
#undef near

zephyr::cbs::Camera::Camera(class Object& object, ID_t id, float fovy, float aspect, float near, float far)
    : Component(object, id)
    , m_Camera(fovy, aspect, near, far) { }

void zephyr::cbs::Camera::Initialize() {
    assert(TransformIn.Connected());

    Object().Scene().Rendering().RegisterCamera(&m_Camera);

    RegisterUpdateCall();
}

void zephyr::cbs::Camera::Update() {
    m_Camera.Update(TransformIn.Value()->GlobalPosition(),
                    TransformIn.Value()->Front(),
                    TransformIn.Value()->Up());
}
