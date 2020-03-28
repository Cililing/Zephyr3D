#include "MainScene.h"

#define STB_IMAGE_IMPLEMENTATION
#include <Zephyr3D/Engine.h>

void MainScene::CreateScene() {
    FrameRateLimit(60);
    Skybox("../../assets/skyboxes/basic_blue/right.png",
           "../../assets/skyboxes/basic_blue/left.png",
           "../../assets/skyboxes/basic_blue/top.png",
           "../../assets/skyboxes/basic_blue/bottom.png",
           "../../assets/skyboxes/basic_blue/back.png",
           "../../assets/skyboxes/basic_blue/front.png");

    auto light = CreateObject("Light"); {
        light->CreateComponent<DirectionalLight>(glm::vec3(-1.0f, -0.5f, -0.5f),
                                                 glm::vec3(0.05f),
                                                 glm::vec3(0.7f, 0.68f, 0.68f),
                                                 glm::vec3(0.8f, 0.78f, 0.78f));
    }

    auto camera = CreateObject("Camera"); {
        camera->Root().Move(glm::vec3(-5.0f, 2.0f, -2.0f));
        camera->Root().Rotate(glm::vec3(0.0f, 0.0f, glm::radians(-15.0f)));
        camera->Root().Rotate(glm::vec3(0.0f, glm::radians(-20.0f), 0.0f));

        auto comp = camera->CreateComponent<Camera>(glm::radians(45.0f), 
                                                    static_cast<float>(zephyr::Engine::Instance().GetWindow().Width()) / static_cast<float>(zephyr::Engine::Instance().GetWindow().Height()),
                                                    0.1f, 
                                                    500.0f);
        camera->Connect(camera->Root().This, comp->TransformIn);
    }
    
    auto cube = CreateObject("Cube"); {
        auto comp = cube->CreateComponent<Cube>(glm::vec3(1.0f, 0.0f, 0.0f));
        cube->Connect(cube->Root().This, comp->TransformIn);
    }
}