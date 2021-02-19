#include "CubeSpawner.h"

#include <Zephyr3D/ZephyrEngine.h>
#include <Zephyr3D/Scene.h>
#include <Zephyr3D/cbs/components/PointLight.h>
#include <Zephyr3D/cbs/components/RigidBody.h>

CubeSpawner::CubeSpawner(class zephyr::cbs::Object& object, ID_t id, float offset)
    : Component(object, id)
    , m_Offset(offset) {
}

void CubeSpawner::Initialize() {
    RegisterUpdateCall();
}

void CubeSpawner::Update() {
    if (zephyr::ZephyrEngine::Instance().Input().KeyPressed(GLFW_KEY_F)) {
        auto object = Object().Scene().CreateObject("Cube");
        object->Root().LocalPosition(Object().Root().LocalPosition() + Object().Root().Front() * m_Offset);

        auto light = object->CreateComponent<zephyr::cbs::PointLight>(1.0f, 0.0014f, 0.000007f, glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));

        auto rb = object->CreateComponent<zephyr::cbs::RigidBody>(0, new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)));
        object->Connect(object->Root().This, rb->TransformIn);

        m_Objects.push_back(object);
    }

    if (zephyr::ZephyrEngine::Instance().Input().KeyPressed(GLFW_KEY_G)) {
        Object().Scene().DestroyObject(m_Objects.back()->ID());
        m_Objects.pop_back();
    }
}
