#include "MainScene.h"

#include <Zephyr3D/init.h>

int main() {
    init();

    MainScene main_scene;
    main_scene.Initialize();
    main_scene.CreateScene();
    main_scene.Run();
    main_scene.Destroy();

    return 0;
}