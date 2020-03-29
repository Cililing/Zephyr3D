#include <Zephyr3D/Engine.h>

#include "MainScene.h"

int main() {
    zephyr::Engine::Instance().Init();

    MainScene main_scene;
    zephyr::Engine::Instance().StartScene(main_scene);

    zephyr::Engine::Instance().Destroy();

    return 0;
}