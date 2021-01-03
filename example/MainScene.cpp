#include "MainScene.h"

#include <Zephyr3D/ZephyrEngine.h>
#include <Zephyr3D/rendering/shaders/SkyboxShader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

MainScene::MainScene(zephyr::Timer& timer, zephyr::InputManager& input)
    : Scene(timer, input) {}

void MainScene::CreateScene() {
    FrameRateLimit(60);

    static_cast<zephyr::rendering::SkyboxShader*>(GetDrawManager().Shader("Skybox"))->SkyboxCubemap(
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
        player->Root().RotateGlobally(glm::vec3(0.0f, 0.0f, glm::radians(-25.0f)));
        player->Root().RotateGlobally(glm::vec3(0.0f, glm::radians(-20.0f), 0.0f));

        auto camera = player->CreateComponent<zephyr::cbs::Camera>(glm::radians(45.0f),
                                                    static_cast<float>(zephyr::ZephyrEngine::Instance().Window().Width()) / static_cast<float>(zephyr::ZephyrEngine::Instance().Window().Height()),
                                                    0.1f, 
                                                    500.0f);
        player->Connect(player->Root().This, camera->TransformIn);

        auto fpc = player->CreateComponent<zephyr::cbs::FirstPersonController>();
        player->Connect(player->Root().This, fpc->TransformIn);

        auto gravity_gun = player->CreateComponent<GravityGun>(10.0f, 5.0f);
        player->Connect(player->Root().This, gravity_gun->TransformIn);

        auto object_spawner = player->CreateComponent<CubeSpawner>(5.0f);
        player->Connect(player->Root().This, object_spawner->TransfromIn);
    }

    auto corrin = CreateObject("Model"); {
        corrin->Root().RotateGlobally(glm::vec3(0.0f, glm::radians(90.0f), 0.0f));
        auto model = corrin->CreateComponent<zephyr::cbs::MeshRenderer>(GetResourcesManager().LoadModel("models/Corrin/scene.gltf"));
        corrin->Connect(corrin->Root().This, model->TransformIn);
    }

    auto elf = CreateObject("Elf"); {
        elf->Root().RotateGlobally(glm::vec3(0.0f, glm::radians(90.0f), glm::radians(90.0f)));
        elf->Root().Move(glm::vec3(5.0f, 0.0f, 0.0f));
        elf->Root().GlobalScale(glm::vec3(0.25f));

        auto model = elf->CreateComponent<zephyr::cbs::MeshRenderer>(GetResourcesManager().LoadModel("models/ElfGirl/scene.gltf"));
        elf->Connect(elf->Root().This, model->TransformIn);
    }

    auto ground = CreateObject("Ground"); {
        ground->Root().GlobalPosition(glm::vec3(0.0f, -5.0f, 0.0f));
        ground->Root().GlobalScale(glm::vec3(20.0f, 1.0f, 20.0f));

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