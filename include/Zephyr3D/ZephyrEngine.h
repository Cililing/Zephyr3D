#ifndef ZephyrEngine_h
#define ZephyrEngine_h

#include "Zephyr3D/utilities/ITimer.h"
#include "Zephyr3D/utilities/Timer.h"
#include "Zephyr3D/utilities/Input.h"
#include "Zephyr3D/utilities/WindowManager.h"
#include "rendering/IDrawManager.h"
#include "physics/IPhysicsManager.h"
#include "resources/ResourcesManager.h"

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <al.h>
#include <alc.h>

#include <iostream>
#include <fstream>
#pragma warning(pop)

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
    void StartScene(Scene& scene);
    void Destroy();

    Timer& Time();
    InputManager& Input();
    WindowManager& GetWindow();
    rendering::IDrawManager& Rendering();
    physics::IPhysicsManager& Physics();
    resources::ResourcesManager& Resources();

private:
    ZephyrEngine() = default;

    Timer m_Time;
    InputManager m_Input;
    WindowManager m_Window;
    Scene* m_CurrentScene{nullptr};
};

}

#endif
