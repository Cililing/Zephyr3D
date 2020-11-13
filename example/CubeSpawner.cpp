#include "CubeSpawner.h"

#include <Zephyr3D/Engine.h>
#include <Zephyr3D/cbs/Object.h>
#include <Zephyr3D/scenes/Scene.h>

CubeSpawner::CubeSpawner(class Object& object, ID_t id, float offset)
    : Component(object, id)
    , m_Offset(offset) {
}

void CubeSpawner::Initialize() {
    RegisterUpdateCall();
}

void CubeSpawner::Update() {
    if (zephyr::Engine::Instance().GetInput().KeyPressed(GLFW_KEY_F)) {
        auto cube = Object().Scene().CreateObject("Cube");
        cube->Root().Position(Object().Root().Position() + Object().Root().Front() * m_Offset);

        auto cb = cube->CreateComponent<Cube>(glm::vec3(1.0f));
        cube->Connect(cube->Root().This, cb->TransformIn);

        auto rb = cube->CreateComponent<RigidBody>(10.0f, new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
        cube->Connect(cube->Root().This, rb->TransformIn);
    }
}
