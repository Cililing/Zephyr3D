#include "MainScene.h"

#include <Zephyr3D/ZephyrEngine.h>
#include <Zephyr3D/rendering/shaders/SkyboxShader.h>
#include <Zephyr3D/cbs/components/Camera.h>
#include <Zephyr3D/cbs/components/DirectionalLight.h>
#include <Zephyr3D/cbs/components/TextRenderer.h>
#include <Zephyr3D/cbs/components/RigidBody.h>
#include <Zephyr3D/cbs/components/FirstPersonController.h>
#include <Zephyr3D/cbs/components/Debuger.h>
#include <Zephyr3D/cbs/components/MeshRenderer.h>
#include <Zephyr3D/cbs/components/SpotLight.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void MainScene::CreateScene() {
    FrameRateLimit(60);

    static_cast<zephyr::rendering::SkyboxShader*>(Rendering().Shader("Skybox"))->SkyboxCubemap(
        zephyr::ZephyrEngine::Instance().Resources().LoadImage("skyboxes/basic_blue/right.png"),
        zephyr::ZephyrEngine::Instance().Resources().LoadImage("skyboxes/basic_blue/left.png"),
        zephyr::ZephyrEngine::Instance().Resources().LoadImage("skyboxes/basic_blue/top.png"),
        zephyr::ZephyrEngine::Instance().Resources().LoadImage("skyboxes/basic_blue/bottom.png"),
        zephyr::ZephyrEngine::Instance().Resources().LoadImage("skyboxes/basic_blue/back.png"),
        zephyr::ZephyrEngine::Instance().Resources().LoadImage("skyboxes/basic_blue/front.png")
    );

    auto light = CreateObject("Light"); {
        auto dir_light = light->CreateComponent<zephyr::cbs::DirectionalLight>(glm::vec3(0.05f),
                                                              glm::vec3(0.7f, 0.68f, 0.68f),
                                                              glm::vec3(0.8f, 0.78f, 0.78f));
        light->Connect(light->Root().This, dir_light->TransformIn);
    }

    auto player = CreateObject("Player"); {
        player->Root().Move(glm::vec3(-10.0f, 4.0f, -2.0f));

        auto camera = player->CreateComponent<zephyr::cbs::Camera>(glm::radians(45.0f),
                                                    static_cast<float>(zephyr::ZephyrEngine::Instance().Window().Width()) / static_cast<float>(zephyr::ZephyrEngine::Instance().Window().Height()),
                                                    0.1f, 
                                                    500.0f);
        player->Connect(player->Root().This, camera->TransformIn);

        auto fpc = player->CreateComponent<zephyr::cbs::FirstPersonController>(15.0f, 1.0f, 0.1f);
        player->Connect(player->Root().This, fpc->TransformIn);

        auto light = player->CreateComponent<zephyr::cbs::SpotLight>(glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), 1.0f, 0.09f, 0.032f, glm::vec3(0.1f), glm::vec3(0.8f), glm::vec3(1.0f));
        player->Connect(player->Root().This, light->TransformIn);

        auto gravity_gun = player->CreateComponent<GravityGun>(10.0f, 5.0f);
        player->Connect(player->Root().This, gravity_gun->TransformIn);

        auto object_spawner = player->CreateComponent<CubeSpawner>(5.0f);
        player->Connect(player->Root().This, object_spawner->TransfromIn);
    }

    auto ground = CreateObject("Ground"); {
        ground->Root().GlobalPosition(glm::vec3(0.0f, -5.0f, 0.0f));
        ground->Root().GlobalScale(glm::vec3(20.0f, 1.0f, 20.0f));

        auto rb = ground->CreateComponent<zephyr::cbs::RigidBody>(0, new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
        ground->Connect(ground->Root().This, rb->TransformIn);
    }

    auto gui = CreateObject("gui"); {
        auto debuger = gui->CreateComponent<zephyr::cbs::Debuger>();
        auto title = gui->CreateComponent<zephyr::cbs::TextRenderer>(zephyr::rendering::IGUIWidget::EAlign::BEGIN, zephyr::rendering::IGUIWidget::EAlign::BEGIN, 0.0f);

        gui->Connect(debuger->DebugInfo, title->TextIn);
    }
}