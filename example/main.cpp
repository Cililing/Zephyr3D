#include <Zephyr3D/ZephyrEngine.h>

#include "MainScene.h"

int main() {
    zephyr::ZephyrEngine::Instance().Initialize(1920u, 1080u, "Zephyr3D example");
    zephyr::ZephyrEngine::Instance().StartScene<MainScene>();
    zephyr::ZephyrEngine::Instance().Destroy();

    return 0;
}