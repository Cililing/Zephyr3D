#include <Zephyr3D/ZephyrEngine.h>

#include "MainScene.h"

int main() {
    zephyr::ZephyrEngine::Instance().Init();

    MainScene main_scene;
    zephyr::ZephyrEngine::Instance().StartScene(main_scene);

    zephyr::ZephyrEngine::Instance().Destroy();

    return 0;
}