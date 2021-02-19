#ifndef Scene_hpp
#define Scene_hpp

#include "physics/PhysicsManager.h"
#include "cbs/ObjectManager.h"
#include "rendering/DrawManager.h"

namespace zephyr {

class IGUIWidget;
class ICamera;
class Clock;
class InputManager;

class Scene {
public:
    Scene();

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(Scene&&) = delete;
    virtual ~Scene() = default;

    void Initialize();
    virtual void PreRun() {}
    virtual void CreateScene() = 0;
    void Run(Clock& clock, InputManager& input_manager);
    virtual void PostRun() {}
    void Destroy();

    void Exit();
    void FrameRateLimit(unsigned int frame_rate);
    float FrameRateLimit() const;
    float FrameRate() const;

    cbs::Object* CreateObject(const std::string& name);
    void DestroyObject(cbs::Object::ID_t id);

    rendering::IDrawManager& Rendering();
    physics::IPhysicsManager& Physics();

private:
    cbs::ObjectManager m_ObjectManager;
    rendering::DrawManager m_DrawManager;
    physics::PhysicsManager m_PhysicsManager;

    float m_FrameRateLimit{ 0.0f };
    bool m_Running{ false };
};

}

#endif
