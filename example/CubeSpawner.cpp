#include "CubeSpawner.h"

#include <Zephyr3D/Engine.h>
#include <Zephyr3D/cbs/Object.h>
#include <Zephyr3D/Scene.h>

CubeSpawner::CubeSpawner(class zephyr::cbs::Object& object, ID_t id, float offset)
    : Component(object, id)
    , m_Offset(offset) {
}

void CubeSpawner::Initialize() {
    RegisterUpdateCall();
}

void CubeSpawner::Update() {
    if (zephyr::ZephyrEngine::Instance().GetInput().KeyPressed(GLFW_KEY_F)) {
        auto cube = Object().Scene().CreateObject("Cube");
        cube->Root().Position(Object().Root().Position() + Object().Root().Front() * m_Offset);

        auto cb = cube->CreateComponent<zephyr::cbs::Cube>(glm::vec3(1.0f));
        cube->Connect(cube->Root().This, cb->TransformIn);

        auto rb = cube->CreateComponent<zephyr::cbs::RigidBody>(10.0f, new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
        cube->Connect(cube->Root().This, rb->TransformIn);
    }
}
