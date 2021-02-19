#ifndef MainScene_h
#define MainScene_h

#include <Zephyr3D/ZephyrEngine.h>
#include <Zephyr3D/Scene.h>

#include "GravityGun.h"
#include "CubeSpawner.h"

class MainScene : public zephyr::Scene {
public:
    void CreateScene() override;
};

#endif
