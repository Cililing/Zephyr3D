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

    // PhysicsManager functions
    void AddCollisionObject(physics::CollisionObject* collision_object, int collision_filter_group = 1, int collision_filter_mask = -1);
    void RemoveCollisionObject(physics::CollisionObject* collision_object);
    void AddRigidBody(physics::CollisionObject* rigid_body, int group = 1, int mask = -1);
    void RemoveRigidBody(physics::CollisionObject* rigid_body);
    void AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies = false);
    void RemoveConstraint(btTypedConstraint* constraint);
    void AddVehicle(btRaycastVehicle* vehicle);
    void RemoveVehicle(btRaycastVehicle* vehicle);
    void Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result);
    void Gravity(const btVector3& gravity);
    btVector3 Gravity() const;
    btDynamicsWorld* DynamicsWorld();

    // ResourceManager functions
    resources::Image& LoadImage(const std::string& path);
    resources::Model& LoadModel(const std::string& path);

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
