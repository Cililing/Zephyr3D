#include <Zephyr3D/ZephyrEngine.h>

#include "MainScene.h"

int main() {
    zephyr::ZephyrEngine::Instance().Init();
    zephyr::ZephyrEngine::Instance().StartScene<MainScene>();
    zephyr::ZephyrEngine::Instance().Destroy();

    return 0;
}