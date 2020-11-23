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
