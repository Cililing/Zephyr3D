#ifndef Engine_h
#define Engine_h

#include "Zephyr3D/utilities/Time.h"
#include "Zephyr3D/utilities/Input.h"
#include "Zephyr3D/utilities/Window.h"

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

class Engine {
public:
    static Engine& Instance() {
        static Engine instance;
        return instance;
    }

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    int Init();
    void StartScene(Scene& scene);
    void Destroy();

    Time& GetTime();
    Input& GetInput();
    Window& GetWindow();

private:
    Engine() {}

    Time m_Time;
    Input m_Input;
    Window m_Window;
};

}

#endif
