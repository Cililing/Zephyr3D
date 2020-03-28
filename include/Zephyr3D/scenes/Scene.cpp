#include "Scene.h"
#include "../Engine.h"

Scene::Scene() 
    : m_ObjectManager(*this)
    , m_PhysicsManager(new PhysicsRenderer(m_DrawManager)) {
}

void Scene::Initialize() {
    m_DrawManager.Initialize();
    m_PhysicsManager.Initialize();
    m_AudioManager.Initialize();
}

void Scene::Run() {
    m_Running = true;

    // Initialize Time manager as close to game loop as possible
    // to avoid misrepresented delta time
    zephyr::Engine::Instance().GetTime().Initialize();
    
    // Game loop
    while (m_Running && !glfwWindowShouldClose(zephyr::Engine::Instance().GetWindow())) {
        // If frame rate is greater than limit then wait
        do {
            zephyr::Engine::Instance().GetTime().Hold();
            glfwPollEvents();
        } while (zephyr::Engine::Instance().GetTime().DeltaTime() < m_FrameRateLimit);
        
        // Update global systems
        zephyr::Engine::Instance().GetTime().Update();
        zephyr::Engine::Instance().GetInput().Update(zephyr::Engine::Instance().GetWindow());
        
        // Update managers
        m_PhysicsManager.StepSimulation(zephyr::Engine::Instance().GetTime().DeltaTime());
        m_ObjectManager.ProcessFrame();
        m_DrawManager.CallDraws();
    }
}

void Scene::Destroy() {
    m_ObjectManager.DestroyObjects();
    m_PhysicsManager.ExitPhysics();
}

void Scene::Exit() {
    m_Running = false;
}

void Scene::FrameRateLimit(unsigned int frame_rate) {
    m_FrameRateLimit = frame_rate != 0 ? 1.0f / (float)frame_rate : 0.0f;
}

float Scene::FrameRateLimit() const {
    return m_FrameRateLimit;
}

float Scene::FrameRate() const {
    return 1.0f / zephyr::Engine::Instance().GetTime().DeltaTime();
}


Object* Scene::CreateObject(const std::string& name) {
    return m_ObjectManager.CreateObject(name);
}

void Scene::DestroyObject(Object::ID_t id) {
    m_ObjectManager.DestroyObject(id);
}


void Scene::RegisterDrawCall(const zephyr::rendering::IDrawable* drawable, zephyr::rendering::EShaderType shader) {
    m_DrawManager.RegisterDrawCall(drawable, shader);
}

void Scene::UnregisterDrawCall(const zephyr::rendering::IDrawable* drawable, zephyr::rendering::EShaderType shader) {
    m_DrawManager.UnregisterDrawCall(drawable, shader);
}

void Scene::RegisterShaderProperty(const zephyr::rendering::IShaderProperty* property, zephyr::rendering::EShaderType shader) {
    m_DrawManager.RegisterShaderProperty(property, shader);
}

void Scene::UnregisterShaderProperty(const zephyr::rendering::IShaderProperty* property, zephyr::rendering::EShaderType shader) {
    m_DrawManager.UnregisterShaderProperty(property, shader);
}

void Scene::RegisterGUIWidget(zephyr::rendering::IGUIWidget* widget) {
    m_DrawManager.RegisterGUIWidget(widget);
}

void Scene::UnregisterGUIWidget(zephyr::rendering::IGUIWidget* widget) {
    m_DrawManager.UnregisterGUIWidget(widget);
}

void Scene::DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
    m_DrawManager.DrawLine(start, end, color);
}

void Scene::DrawPlane(glm::mat4 model, glm::vec3 color) {
    m_DrawManager.DrawPlane(model, color);
}

void Scene::DrawCuboid(glm::mat4 model, glm::vec3 color) {
    m_DrawManager.DrawCuboid(model, color);
}

void Scene::DrawSphere(glm::mat4 model, glm::vec3 color) {
    //TODO
}

void Scene::RegisterCamera(Camera* camera) {
    m_DrawManager.RegisterCamera(camera);
}

Camera* Scene::MainCamera() const {
    return m_DrawManager.MainCamera();
}

void Scene::Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front) {
    m_DrawManager.Skybox(right, left, top, bottom, back, front);
}

void Scene::Background(const glm::vec3& background) {
    m_DrawManager.Background(background);
}


void Scene::AddCollisionObject(btCollisionObject* collision_object, int collision_filter_group, int collision_filter_mask) {
    m_PhysicsManager.AddCollisionObject(collision_object, collision_filter_group, collision_filter_mask);
}

void Scene::RemoveCollisionObject(btCollisionObject* collision_object) {
    m_PhysicsManager.RemoveCollisionObject(collision_object);
}

void Scene::AddRigidBody(btRigidBody* rigid_body, int group, int mask) {
    m_PhysicsManager.AddRigidBody(rigid_body, group, mask);
}

void Scene::RemoveRigidBody(btRigidBody* rigid_body) {
    m_PhysicsManager.RemoveRigidBody(rigid_body);
}

void Scene::AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies) {
    m_PhysicsManager.AddConstraint(constraint, disable_collisions_between_linked_bodies);
}

void Scene::RemoveConstraint(btTypedConstraint* constraint) {
    m_PhysicsManager.RemoveConstraint(constraint);
}

void Scene::AddVehicle(btRaycastVehicle* vehicle) {
    m_PhysicsManager.AddVehicle(vehicle);
}

void Scene::RemoveVehicle(btRaycastVehicle* vehicle) {
    m_PhysicsManager.RemoveVehicle(vehicle);
}

void Scene::Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result) {
    m_PhysicsManager.Raycast(from, to, result);
}

void Scene::Gravity(const btVector3& gravity) {
    m_PhysicsManager.Gravity(gravity);
}

btVector3 Scene::Gravity() const {
    return m_PhysicsManager.Gravity();
}

btDynamicsWorld* Scene::DynamicsWorld() {
    return m_PhysicsManager.DynamicsWorld();
}


void Scene::ListenerPosition(float x, float y, float z) {
    m_AudioManager.ListenerPosition(x, y, z);
}

void Scene::ListenerVelocity(float x, float y, float z) {
    m_AudioManager.ListenerVelocity(x, y, z);
}

void Scene::ListenerGain(float gain) {
    m_AudioManager.ListenerGain(gain);
}

void Scene::ListenerOrientation(float at_x, float at_y, float at_z, float up_x, float up_y, float up_z) {
    m_AudioManager.ListenerOrientation(at_x, at_y, at_z, up_x, up_y, up_z);
}


RawTexture& Scene::LoadTexture(const std::string& path) {
    return m_ResourceManager.LoadTexture(path);
}

RawModel& Scene::LoadModel(const std::string& path) {
    return m_ResourceManager.LoadModel(path);
}

Sound& Scene::LoadSound(const std::string& path) {
    return m_ResourceManager.LoadSound(path);
}
