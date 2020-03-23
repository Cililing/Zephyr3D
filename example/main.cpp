#include "MainScene.h"

#define STB_IMAGE_IMPLEMENTATION
#include <Zephyr3D/Engine.h>

int main() {
    Engine::Instance().Init();

    MainScene main_scene;
    main_scene.Initialize();
    main_scene.CreateScene();
    main_scene.Run();
    main_scene.Destroy();

    Engine::Instance().Destroy();

    return 0;
}