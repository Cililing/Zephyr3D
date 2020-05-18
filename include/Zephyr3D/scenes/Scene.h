#ifndef Scene_hpp
#define Scene_hpp

#include "../physics/PhysicsManager.h"
#include "../cbs/ObjectManager.h"
#include "../rendering/DrawManager.h"
#include "../resources/ResourcesManager.h"
#include "../audio/AudioManager.h"

#include "../utilities/Time.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"

#undef LoadImage

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

    // 
    void Initialize();
    virtual void PreRun() {}
    virtual void CreateScene() = 0;
    void Run();
    virtual void PostRun() {}
    void Destroy();

    // Scene functions
    void Exit();
    void FrameRateLimit(unsigned int frame_rate);
    float FrameRateLimit() const;
    float FrameRate() const;

    // ObjectManager functions
    Object* CreateObject(const std::string& name);
    void DestroyObject(Object::ID_t id);

    // DrawManager functions
    void RegisterDrawCall(const zephyr::rendering::IDrawable* drawable, const std::string& shader_name);
    void UnregisterDrawCall(const zephyr::rendering::IDrawable* drawable, const std::string& shader_name);
    void RegisterShaderProperty(const zephyr::rendering::IShaderProperty* property, const std::string& shader_name);
    void UnregisterShaderProperty(const zephyr::rendering::IShaderProperty* property, const std::string& shader_name);
    void RegisterGUIWidget(zephyr::rendering::IGUIWidget* widget);
    void UnregisterGUIWidget(zephyr::rendering::IGUIWidget* widget);
    void RegisterCamera(zephyr::rendering::ICamera* camera);
    zephyr::rendering::ICamera* MainCamera() const;
    void Skybox(const zephyr::resources::Image& right, const zephyr::resources::Image& left, const zephyr::resources::Image& top, const zephyr::resources::Image& bottom, const zephyr::resources::Image& back, const zephyr::resources::Image& front);
    zephyr::rendering::ShaderProgram* Shader(const std::string& name);
    void Background(const glm::vec3& background);

    // PhysicsManager functions
    void AddCollisionObject(btCollisionObject* collision_object, int collision_filter_group = 1, int collision_filter_mask = -1);
    void RemoveCollisionObject(btCollisionObject* collision_object);
    void AddRigidBody(btRigidBody* rigid_body, int group = 1, int mask = -1);
    void RemoveRigidBody(btRigidBody* rigid_body);
    void AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies = false);
    void RemoveConstraint(btTypedConstraint* constraint);
    void AddVehicle(btRaycastVehicle* vehicle);
    void RemoveVehicle(btRaycastVehicle* vehicle);
    void Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result);
    void Gravity(const btVector3& gravity);
    btVector3 Gravity() const;
    btDynamicsWorld* DynamicsWorld();

    // AudioManager functions
    void ListenerPosition(float x, float y, float z);
    void ListenerVelocity(float x, float y, float z);
    void ListenerGain(float gain);
    void ListenerOrientation(float at_x, float at_y, float at_z, float up_x, float up_y, float up_z);

    // ResourceManager functions
    zephyr::resources::Image& LoadImage(const std::string& path);
    zephyr::resources::Model& LoadModel(const std::string& path);
    zephyr::resources::AudioClip& LoadAudioClip(const std::string& path);

private:
    ObjectManager m_ObjectManager;
    zephyr::rendering::DrawManager m_DrawManager;
    zephyr::physics::PhysicsManager m_PhysicsManager;
    AudioManager m_AudioManager;
    zephyr::resources::ResourcesManager m_ResourceManager;

    bool m_Running{ false };
    float m_FrameRateLimit{ 0.0f };
};

#endif
