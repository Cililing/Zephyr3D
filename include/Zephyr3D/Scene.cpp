#include "Scene.h"
#include "rendering/ICamera.h"
#include "rendering/IDrawable.h"
#include "rendering/IGUIWidget.h"
#include "rendering/Cubemap.h"

#include "ZephyrEngine.h"

zephyr::Scene::Scene()
    : m_ObjectManager(*this)
    , m_PhysicsManager(m_DrawManager) {
}

void zephyr::Scene::Initialize() {
    m_DrawManager.Initialize();
    m_PhysicsManager.Initialize();
    //m_ObjectManager.InitializeObjects();
}

void zephyr::Scene::Run(Clock& clock, InputManager& input_manager) {
    m_Running = true;

    // Initialize Time manager as close to game loop as possible
    // to avoid misrepresented delta time
    clock.Initialize();
    
    // Game loop
    while (m_Running && !ZephyrEngine::Instance().Window().ShouldClose()) {
        clock.Update();
        input_manager.Update(ZephyrEngine::Instance().Window().Handle());

        while (clock.DeltaTime() < m_FrameRateLimit) {
            clock.HoldFrame();
            glfwPollEvents();
        }

        // Update managers
        m_PhysicsManager.StepSimulation(zephyr::ZephyrEngine::Instance().Time().DeltaTime());
        m_ObjectManager.ProcessFrame();
        m_DrawManager.CallDraws();

        glfwPollEvents();
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
    return 1.0f / ZephyrEngine::Instance().Time().DeltaTime();
}

zephyr::cbs::Object* zephyr::Scene::CreateObject(const std::string& name) {
    return m_ObjectManager.CreateObject(name);
}

void zephyr::Scene::DestroyObject(zephyr::cbs::Object::ID_t id) {
    m_ObjectManager.DestroyObject(id);
}

zephyr::rendering::IDrawManager& zephyr::Scene::Rendering() {
    return m_DrawManager;
}

zephyr::physics::IPhysicsManager& zephyr::Scene::Physics() {
    return m_PhysicsManager;
}
