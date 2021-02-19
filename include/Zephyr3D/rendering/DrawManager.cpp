#include "DrawManager.h"
#include "ICamera.h"
#include "IDrawable.h"
#include "IGUIWidget.h"
#include "shaders/PureColor.h"
#include "shaders/PureTexture.h"
#include "shaders/Phong.h"

#include "../ZephyrEngine.h"
#include "../utilities/WindowManager.h"
#include "../cbs/components/Camera.h"

void zephyr::rendering::DrawManager::Initialize() {
    INFO_LOG(Logger::ESender::Rendering, "Initializing draw manager");

    // Dear imgui initialiation
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(ZephyrEngine::Instance().Window(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Load default font
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    // Create common shaders
    {auto [it, vld] = m_Shaders.try_emplace("PureColor", std::make_unique<PureColor>());
    if (!vld) {
        ERROR_LOG(Logger::ESender::Rendering, "Failed to emplace PureColor shader\n");
    }}

    {auto [it, vld] = m_Shaders.try_emplace("PureTexture", std::make_unique<PureTexture>());
    if (!vld) {
        ERROR_LOG(Logger::ESender::Rendering, "Failed to emplace PureTexture shader\n");
    }}

    {auto [it, vld] = m_Shaders.try_emplace("Phong", std::make_unique<Phong>());
    if (!vld) {
        ERROR_LOG(Logger::ESender::Rendering, "Failed to emplace Phong shader\n");
    }}

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void zephyr::rendering::DrawManager::Destroy() {
    INFO_LOG(Logger::ESender::Rendering, "Destroying draw manager");
}

void zephyr::rendering::DrawManager::RegisterCamera(ICamera *camera) {
    m_Camera = camera;
}

zephyr::rendering::ICamera* zephyr::rendering::DrawManager::MainCamera() const {
    return m_Camera;
}

void zephyr::rendering::DrawManager::ClearColor(const glm::vec3& background) {
    m_Background = background;
}

glm::vec3 zephyr::rendering::DrawManager::ClearColor() const {
    return m_Background;
}

void zephyr::rendering::DrawManager::RegisterGUIWidget(IGUIWidget* widget) {
    assert(std::find(m_GUIWidgets.begin(), m_GUIWidgets.end(), widget) == m_GUIWidgets.end());

    m_GUIWidgets.push_back(widget);
}

void zephyr::rendering::DrawManager::UnregisterGUIWidget(IGUIWidget* widget) {
    auto to_erase = std::find(m_GUIWidgets.begin(), m_GUIWidgets.end(), widget);
    if (to_erase != m_GUIWidgets.end()) {
        m_GUIWidgets.erase(to_erase);
    }
}

void zephyr::rendering::DrawManager::CallDraws() {
    glClearColor(m_Background.x, m_Background.y, m_Background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Call draws in all shaders
    for (auto it = m_Shaders.begin(); it != m_Shaders.end(); it++) {
        auto& shader = it->second;

        shader->Use();
        shader->Draw(m_Camera);
    }

    glm::mat4 pv = m_Camera->Projection() * m_Camera->View();

    // Draw debug
    m_DebugShader.Use();
    m_DebugShader.Draw(m_Camera);

    // Draw skybox
    m_SkyboxShader.Use();
    m_SkyboxShader.Draw(m_Camera);

    // Draw GUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto widget = m_GUIWidgets.begin(); widget != m_GUIWidgets.end(); widget++) {
        (*widget)->Draw();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();

    // End of drawing
    glfwSwapBuffers(ZephyrEngine::Instance().Window());
}

zephyr::rendering::ShaderProgram* zephyr::rendering::DrawManager::Shader(const std::string& name) {
    // Special case shaders
    if (name == "Debug")
        return &m_DebugShader;
    if (name == "Skybox")
        return &m_SkyboxShader;

    assert(m_Shaders.find(name) != m_Shaders.end());
    return m_Shaders.at(name).get();
}
