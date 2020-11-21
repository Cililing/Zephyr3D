#include "Scene.h"
#include "rendering/ICamera.h"
#include "rendering/IDrawable.h"
#include "rendering/IShaderProperty.h"
#include "rendering/IGUIWidget.h"
#include "rendering/Cubemap.h"

#include "Engine.h"

zephyr::Scene::Scene() 
    : m_ObjectManager(*this)
    , m_PhysicsManager(m_DrawManager) {
}

void zephyr::Scene::Initialize() {
    m_DrawManager.Initialize();
    m_PhysicsManager.Initialize();
    m_ObjectManager.InitializeObjects();
}

void zephyr::Scene::Run() {
    m_Running = true;

    // Initialize Time manager as close to game loop as possible
    // to avoid misrepresented delta time
    zephyr::ZephyrEngine::Instance().GetTime().Initialize();
    
    // Game loop
    while (m_Running && !glfwWindowShouldClose(zephyr::ZephyrEngine::Instance().GetWindow())) {
        // If frame rate is greater than limit then wait
        do {
            zephyr::ZephyrEngine::Instance().GetTime().Hold();
            glfwPollEvents();
        } while (zephyr::ZephyrEngine::Instance().GetTime().DeltaTime() < m_FrameRateLimit);
        
        // Update global systems
        zephyr::ZephyrEngine::Instance().GetTime().Update();
        zephyr::ZephyrEngine::Instance().GetInput().Update(zephyr::ZephyrEngine::Instance().GetWindow());
        
        // Update managers
        m_PhysicsManager.StepSimulation(zephyr::ZephyrEngine::Instance().GetTime().DeltaTime());
        m_ObjectManager.ProcessFrame();
        m_DrawManager.CallDraws();
    }
}

void zephyr::Scene::Destroy() {
    m_DrawManager.Destroy();
    m_ObjectManager.DestroyObjects();
    m_PhysicsManager.ExitPhysics();
}

void zephyr::Scene::Exit() {
    m_Running = false;
}

void zephyr::Scene::FrameRateLimit(unsigned int frame_rate) {
    m_FrameRateLimit = frame_rate != 0 ? 1.0f / (float)frame_rate : 0.0f;
}

float zephyr::Scene::FrameRateLimit() const {
    return m_FrameRateLimit;
}

float zephyr::Scene::FrameRate() const {
    return 1.0f / zephyr::ZephyrEngine::Instance().GetTime().DeltaTime();
}



zephyr::cbs::Object* zephyr::Scene::CreateObject(const std::string& name) {
    return m_ObjectManager.CreateObject(name);
}

void zephyr::Scene::DestroyObject(zephyr::cbs::Object::ID_t id) {
    m_ObjectManager.DestroyObject(id);
}


void zephyr::Scene::RegisterDrawCall(const zephyr::rendering::IDrawable* drawable, const std::string& shader_name) {
    m_DrawManager.RegisterDrawCall(drawable, shader_name);
}

void zephyr::Scene::UnregisterDrawCall(const zephyr::rendering::IDrawable* drawable, const std::string& shader_name) {
    m_DrawManager.UnregisterDrawCall(drawable, shader_name);
}

void zephyr::Scene::RegisterShaderProperty(const zephyr::rendering::IShaderProperty* property, const std::string& shader_name) {
    m_DrawManager.RegisterShaderProperty(property, shader_name);
}

void zephyr::Scene::UnregisterShaderProperty(const zephyr::rendering::IShaderProperty* property, const std::string& shader_name) {
    m_DrawManager.UnregisterShaderProperty(property, shader_name);
}

void zephyr::Scene::RegisterGUIWidget(zephyr::rendering::IGUIWidget* widget) {
    m_DrawManager.RegisterGUIWidget(widget);
}

void zephyr::Scene::UnregisterGUIWidget(zephyr::rendering::IGUIWidget* widget) {
    //m_DrawManager.UnregisterGUIWidget(widget);
}

void zephyr::Scene::RegisterCamera(zephyr::rendering::ICamera* camera) {
    m_DrawManager.RegisterCamera(camera);
}

zephyr::rendering::ICamera* zephyr::Scene::MainCamera() const {
    return m_DrawManager.MainCamera();
}

void zephyr::Scene::Skybox(const zephyr::resources::Image& right, const zephyr::resources::Image& left, const zephyr::resources::Image& top, const zephyr::resources::Image& bottom, const zephyr::resources::Image& back, const zephyr::resources::Image& front) {
    m_DrawManager.Skybox(right, left, top, bottom, back, front);
}

zephyr::rendering::ShaderProgram* zephyr::Scene::Shader(const std::string& name) {
    return m_DrawManager.Shader(name);
}

void zephyr::Scene::Background(const glm::vec3& background) {
    m_DrawManager.Background(background);
}


void zephyr::Scene::AddCollisionObject(zephyr::physics::CollisionObject* collision_object, int collision_filter_group, int collision_filter_mask) {
    m_PhysicsManager.AddCollisionObject(collision_object, collision_filter_group, collision_filter_mask);
}

void zephyr::Scene::RemoveCollisionObject(zephyr::physics::CollisionObject* collision_object) {
    m_PhysicsManager.RemoveCollisionObject(collision_object);
}

void zephyr::Scene::AddRigidBody(zephyr::physics::CollisionObject* rigid_body, int group, int mask) {
    m_PhysicsManager.AddRigidBody(rigid_body, group, mask);
}

void zephyr::Scene::RemoveRigidBody(zephyr::physics::CollisionObject* rigid_body) {
    m_PhysicsManager.RemoveRigidBody(rigid_body);
}

void zephyr::Scene::AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies) {
    m_PhysicsManager.AddConstraint(constraint, disable_collisions_between_linked_bodies);
}

void zephyr::Scene::RemoveConstraint(btTypedConstraint* constraint) {
    m_PhysicsManager.RemoveConstraint(constraint);
}

void zephyr::Scene::AddVehicle(btRaycastVehicle* vehicle) {
    m_PhysicsManager.AddVehicle(vehicle);
}

void zephyr::Scene::RemoveVehicle(btRaycastVehicle* vehicle) {
    m_PhysicsManager.RemoveVehicle(vehicle);
}

void zephyr::Scene::Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result) {
    m_PhysicsManager.Raycast(from, to, result);
}

void zephyr::Scene::Gravity(const btVector3& gravity) {
    m_PhysicsManager.Gravity(gravity);
}

btVector3 zephyr::Scene::Gravity() const {
    return m_PhysicsManager.Gravity();
}

btDynamicsWorld* zephyr::Scene::DynamicsWorld() {
    return m_PhysicsManager.DynamicsWorld();
}


zephyr::resources::Image& zephyr::Scene::LoadImage(const std::string& path) {
    return m_ResourceManager.LoadImage(path);
}

zephyr::resources::Model& zephyr::Scene::LoadModel(const std::string& path) {
    return m_ResourceManager.LoadModel(path);
}
