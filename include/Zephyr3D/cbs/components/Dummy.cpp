#include "Dummy.h"

#include "../Object.h"
#include "../../scenes/Scene.h"

void Dummy::Initialize() {
    RegisterUpdateCall();
}

void Dummy::Update() {
    if (g_Input.KeyPressed(GLFW_MOUSE_BUTTON_1)) {
        btVector3 start(0.0f, -0.5f, -4.0f);
        btVector3 end(0.0f, -0.5f, 4.0f);
        btDynamicsWorld::ClosestRayResultCallback raycast(start, end);

        Object().Scene().Raycast(start, end, raycast);
        Object().Scene().DrawLine(glm::vec3(0.0f, -0.5f, -4.0f), glm::vec3(0.0f, -0.5f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
}
