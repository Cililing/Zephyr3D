#include "Debuger.h"
#include "../Object.h"
#include "../../Scene.h"
#include "../../ZephyrEngine.h"

zephyr::cbs::Debuger::Debuger(class Object& object, ID_t id)
    : Component(object, id) { }

void zephyr::cbs::Debuger::Initialize() {
    RegisterUpdateCall();
}

void zephyr::cbs::Debuger::Update() {
    auto fps = std::to_string(1.0f / ZephyrEngine::Instance().Time().DeltaTime());

    std::string msg = 
        "Zephyr3D alpha scene\n"
        CONFIGURATION
        "\nfps: " + fps;

    DebugInfo.Send(msg);
}
