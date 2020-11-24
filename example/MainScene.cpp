#include "MainScene.h"

#include <Zephyr3D/ZephyrEngine.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void MainScene::CreateScene() {
    FrameRateLimit(60);

    GetDrawManager().Skybox(
        GetResourcesManager().LoadImage("skyboxes/basic_blue/right.png"),
        GetResourcesManager().LoadImage("skyboxes/basic_blue/left.png"),
        GetResourcesManager().LoadImage("skyboxes/basic_blue/top.png"),
        GetResourcesManager().LoadImage("skyboxes/basic_blue/bottom.png"),
        GetResourcesManager().LoadImage("skyboxes/basic_blue/back.png"),
        GetResourcesManager().LoadImage("skyboxes/basic_blue/front.png")
    );

    auto light = CreateObject("Light"); {
        light->CreateComponent<zephyr::cbs::DirectionalLight>(glm::vec3(-1.0f, -0.5f, -0.5f),
                                                 glm::vec3(0.05f),
                                                 glm::vec3(0.7f, 0.68f, 0.68f),
                                                 glm::vec3(0.8f, 0.78f, 0.78f));
    }

    auto player = CreateObject("Player"); {
        player->Root().Move(glm::vec3(-10.0f, 4.0f, -2.0f));
        player->Root().Rotate(glm::vec3(0.0f, 0.0f, glm::radians(-25.0f)));
        player->Root().Rotate(glm::vec3(0.0f, glm::radians(-20.0f), 0.0f));

        auto comp = player->CreateComponent<zephyr::cbs::Camera>(glm::radians(45.0f),
                                                    static_cast<float>(zephyr::ZephyrEngine::Instance().GetWindow().Width()) / static_cast<float>(zephyr::ZephyrEngine::Instance().GetWindow().Height()),
                                                    0.1f, 
                                                    500.0f);
        player->Connect(player->Root().This, comp->TransformIn);

        auto fpc = player->CreateComponent<zephyr::cbs::FirstPersonController>();
        player->Connect(player->Root().This, fpc->TransformIn);

        auto gravity_gun = player->CreateComponent<GravityGun>(10.0f, 5.0f);
        player->Connect(player->Root().This, gravity_gun->TransformIn);

        auto object_spawner = player->CreateComponent<CubeSpawner>(5.0f);
        player->Connect(player->Root().This, object_spawner->TransfromIn);
    }

    for (auto i = 0; i < 3; i++) {
        for (auto j = 0; j < 3; j++) {
            for (auto k = 0; k < 3; k++) {
                auto cube = CreateObject("Cube"); {
                    cube->Root().Position(glm::vec3(i, j, k));

                    auto comp = cube->CreateComponent<zephyr::cbs::Cube>(glm::vec3((float)i / 3.0f, (float)j / 3.0f, (float)k / 3.0f));
                    cube->Connect(cube->Root().This, comp->TransformIn);

                    auto rb = cube->CreateComponent<zephyr::cbs::RigidBody>(10.0f * (i + 1) * (j + 1) * (k + 1), new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
                    cube->Connect(cube->Root().This, rb->TransformIn);
                }
            }
        }
    }

    auto ground = CreateObject("Ground"); {
        ground->Root().Position(glm::vec3(0.0f, -5.0f, 0.0f));
        ground->Root().Scale(glm::vec3(20.0f, 1.0f, 20.0f));

        auto cube = ground->CreateComponent<zephyr::cbs::Cube>(glm::vec3(1.0f, 0.0f, 0.0f));
        ground->Connect(ground->Root().This, cube->TransformIn);

        auto rb = ground->CreateComponent<zephyr::cbs::RigidBody>(0, new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
        ground->Connect(ground->Root().This, rb->TransformIn);
    }

    auto gui = CreateObject("gui"); {
        auto debuger = gui->CreateComponent<zephyr::cbs::Debuger>();
        auto title = gui->CreateComponent<zephyr::cbs::TextRenderer>(zephyr::rendering::IGUIWidget::EAlign::BEGIN, zephyr::rendering::IGUIWidget::EAlign::BEGIN, 0.0f);

        gui->Connect(debuger->DebugInfo, title->TextIn);
    }
}