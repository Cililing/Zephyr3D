#ifndef Timer_h
#define Timer_h

#include "ITimer.h"

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

namespace zephyr {

constexpr auto FPS_LIMIT30 = (1.0f / 30.0f);
constexpr auto FPS_LIMIT60 = (1.0f / 60.0f);
constexpr auto FPS_LIMIT300 = (1.0f / 300.0f);

class Timer : public ITimer {
public:
    Timer();
    
    void Initialize();
    void HoldFrame();
    void Update();
    
    float CurrentTime() const { return static_cast<float>(glfwGetTime()); }
    float DeltaTime() const { return m_DeltaTime; }
 
private:
    float m_CurrentTime;
    float m_DeltaTime;
    float m_LastFrame;
};

}

#endif
