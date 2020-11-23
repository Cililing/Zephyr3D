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
