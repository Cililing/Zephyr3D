#include "MainScene.h"
#include <Zephyr3D/Engine.h>

int main() {
    zephyr::Engine::Instance().Init();

    MainScene main_scene;
    main_scene.Initialize();
    main_scene.CreateScene();
    main_scene.Run();
    main_scene.Destroy();

    zephyr::Engine::Instance().Destroy();

    return 0;
}