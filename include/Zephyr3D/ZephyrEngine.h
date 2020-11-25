#ifndef ZephyrEngine_h
#define ZephyrEngine_h

#include "Zephyr3D/utilities/ITimer.h"
#include "Zephyr3D/utilities/Timer.h"
#include "Zephyr3D/utilities/Input.h"
#include "Zephyr3D/utilities/IWindow.h"
#include "Zephyr3D/utilities/WindowManager.h"
#include "rendering/IDrawManager.h"
#include "physics/IPhysicsManager.h"
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

    int Init();
    void Destroy();

    template <class T>
    void StartScene() {
        T scene(m_Timer, m_InputManager);

        scene.Initialize();
        scene.CreateScene();
        scene.Run();
        scene.Destroy();
    }
    

    Timer& Time();
    IInput& Input();
    IWindow& Window();

private:
    ZephyrEngine() = default;

    Timer m_Timer;
    InputManager m_InputManager;
    WindowManager m_WindowManager;
};

}

#endif
