#ifndef Clock_h
#define Clock_h

#include "IClock.h"

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

namespace zephyr {

constexpr auto FPS_LIMIT30 = (1.0f / 30.0f);
constexpr auto FPS_LIMIT60 = (1.0f / 60.0f);
constexpr auto FPS_LIMIT300 = (1.0f / 300.0f);

class Clock : public IClock {
public:    
    void Initialize();
    void HoldFrame();
    void Update();
    
    float CurrentTime() const override;
    float DeltaTime() const override;
 
private:
    float m_CurrentTime{ 0.0f };
    float m_DeltaTime{ 0.0f };
    float m_LastFrame{ 0.0f };
};

}

#endif
