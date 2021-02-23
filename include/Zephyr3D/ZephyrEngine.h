#ifndef ZephyrEngine_h
#define ZephyrEngine_h

#include "core/Clock.h"
#include "core/Input.h"
#include "core/WindowManager.h"
#include "resources/ResourcesManager.h"

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <iostream>
#include <fstream>
#include <type_traits>
#include <assert.h>

namespace zephyr {

class Scene;

class ZephyrEngine {
public:
    static ZephyrEngine& Instance() {
        static ZephyrEngine instance;
        return instance;
    }

    ZephyrEngine(const ZephyrEngine&) = delete;
    ZephyrEngine& operator=(const ZephyrEngine&) = delete;
    ZephyrEngine(ZephyrEngine&&) = delete;
    ZephyrEngine& operator=(ZephyrEngine&&) = delete;

    void Initialize(unsigned int window_width, unsigned int window_height, const std::string& window_title);
    void Destroy();

    template <class T>
    void StartScene() {
        T scene;

        scene.Initialize();
        scene.CreateScene();
        scene.Run(m_Clock, m_InputManager);
        scene.Destroy();
    }

    IClock& Time();
    IInput& Input();
    IWindow& Window();
    resources::ResourcesManager& Resources();

private:
    ZephyrEngine() = default;

    Clock m_Clock;
    InputManager m_InputManager;
    WindowManager m_WindowManager;
    resources::ResourcesManager m_ResourceManager;
};

}

#endif
