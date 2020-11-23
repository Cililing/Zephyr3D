#ifndef Scene_hpp
#define Scene_hpp

#include "physics/PhysicsManager.h"
#include "cbs/ObjectManager.h"
#include "rendering/DrawManager.h"
#include "rendering/IDrawManager.h"
#include "resources/ResourcesManager.h"

#include "utilities/Time.h"
#include "utilities/Input.h"
#include "utilities/Window.h"

#undef LoadImage

namespace zephyr {

class IGUIWidget;
class ICamera;

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
    void Run();
    virtual void PostRun() {}
    void Destroy();

    void Exit();
    void FrameRateLimit(unsigned int frame_rate);
    float FrameRateLimit() const;
    float FrameRate() const;

    cbs::Object* CreateObject(const std::string& name);
    void DestroyObject(cbs::Object::ID_t id);

    rendering::IDrawManager& GetDrawManager() { return m_DrawManager; }
    physics::IPhysicsManager& GetPhysicsManager() { return m_PhysicsManager; }
    resources::ResourcesManager& GetResourcesManager() { return m_ResourceManager; }

private:
    cbs::ObjectManager m_ObjectManager;
    rendering::DrawManager m_DrawManager;
    physics::PhysicsManager m_PhysicsManager;
    resources::ResourcesManager m_ResourceManager;

    bool m_Running{ false };
    float m_FrameRateLimit{ 0.0f };
};

}

#endif
