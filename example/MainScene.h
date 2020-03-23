#ifndef MainScene_h
#define MainScene_h


#include <Zephyr3D/scenes/Scene.h>
#include <Zephyr3D/cbs/components/Camera.h>
#include <Zephyr3D/cbs/components/DirectionalLight.h>
#include <Zephyr3D/cbs/components/Cube.h>

class MainScene : public Scene {
public:
    void CreateScene() override;
};

#endif
