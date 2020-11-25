#include "DrawManager.h"
#include "ICamera.h"
#include "IDrawable.h"
#include "IShaderProperty.h"
#include "IGUIWidget.h"
#include "Cubemap.h"

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

void zephyr::rendering::DrawManager::Skybox(const resources::Image& right, const resources::Image& left, const resources::Image& top, const resources::Image& bottom, const resources::Image& back, const resources::Image& front) {
    m_Skybox = std::make_unique<Cubemap>(right, left, top, bottom, back, front);
}

void zephyr::rendering::DrawManager::ClearColor(const glm::vec3& background) {
    m_Background = background;
}

glm::vec3 zephyr::rendering::DrawManager::ClearColor() const {
    return glm::vec3();
}

void zephyr::rendering::DrawManager::RegisterDrawCall(const IDrawable* drawable, const std::string& shader_name) {
    m_Shaders.at(shader_name)->RegisterDrawCall(drawable);
}

void zephyr::rendering::DrawManager::UnregisterDrawCall(const IDrawable* drawable, const std::string& shader_name) {
    m_Shaders.at(shader_name)->UnregisterDrawCall(drawable);
}

void zephyr::rendering::DrawManager::RegisterShaderProperty(const IShaderProperty* property, const std::string& shader_name) {
    m_Shaders.at(shader_name)->RegisterShaderProperty(property);
}

void zephyr::rendering::DrawManager::UnregisterShaderProperty(const IShaderProperty* property, const std::string& shader_name) {
    m_Shaders.at(shader_name)->UnregisterShaderProperty(property);
}

void zephyr::rendering::DrawManager::RegisterGUIWidget(IGUIWidget* widget) {
    // Ensure that each widget is registered at most once
    assert(std::find(m_GUIWidgets.begin(), m_GUIWidgets.end(), widget) == m_GUIWidgets.end());

    m_GUIWidgets.push_back(widget);
}

void zephyr::rendering::DrawManager::UnregisterGUIWidget(IGUIWidget* widget) {
    // Unregistering not registered widget has no effect
    auto to_erase = std::find(m_GUIWidgets.begin(), m_GUIWidgets.end(), widget);
    if (to_erase != m_GUIWidgets.end()) {
        m_GUIWidgets.erase(to_erase);
    }
}

void zephyr::rendering::DrawManager::CallDraws() {
    glClearColor(m_Background.x, m_Background.y, m_Background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 pv = m_Camera->Projection() * m_Camera->View();

    // Call draws in all shaders
    for (auto it = m_Shaders.begin(); it != m_Shaders.end(); it++) {
        auto& shader = it->second;

        shader->Use();

        shader->Uniform("pv", pv);
        shader->Uniform("viewPos", m_Camera->Position());

        shader->CallProperties();
        shader->CallDraws();
    }

    m_DebugShader.Use();
    m_DebugShader.Uniform("pv", pv);
    m_DebugShader.CallDraws();

    // Draw skybox
    if (m_Skybox != nullptr) {
        glDepthFunc(GL_LEQUAL);

        m_SkyboxShader.Use();
        m_SkyboxShader.Uniform("pv", m_Camera->Projection() * glm::mat4(glm::mat3(m_Camera->View())));

        m_Skybox->Draw(m_SkyboxShader);

        glDepthFunc(GL_LESS);
    }

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
    if (name == "Shybox")
        return &m_SkyboxShader;

    assert(m_Shaders.find(name) != m_Shaders.end());
    return m_Shaders.at(name).get();
}
