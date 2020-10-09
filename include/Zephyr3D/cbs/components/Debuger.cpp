#include "Debuger.h"

Debuger::Debuger(class Object& object, ID_t id)
    : Component(object, id) {

}

void Debuger::Initialize() {
    RegisterUpdateCall();
}

void Debuger::Update() {
    auto fps = std::to_string(1.0f / zephyr::Engine::Instance().GetTime().DeltaTime());

    std::string msg = 
        "Zephyr3D alpha scene\n"
        "fps: " + fps;

    DebugInfo.Send(msg);
}
