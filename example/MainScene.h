#ifndef MainScene_h
#define MainScene_h

#include <Zephyr3D/Scene.h>
#include <Zephyr3D/cbs/components/Camera.h>
#include <Zephyr3D/cbs/components/DirectionalLight.h>
#include <Zephyr3D/cbs/components/Cube.h>
#include <Zephyr3D/cbs/components/TextRenderer.h>
#include <Zephyr3D/cbs/components/RigidBody.h>
#include <Zephyr3D/cbs/components/FirstPersonController.h>
#include <Zephyr3D/cbs/components/Debuger.h>
#include <Zephyr3D/cbs/components/MeshRenderer.h>

#include "GravityGun.h"
#include "CubeSpawner.h"

class MainScene : public zephyr::Scene {
public:
    void CreateScene() override;
};

#endif
