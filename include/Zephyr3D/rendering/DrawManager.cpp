#include "DrawManager.h"

#include "../Engine.h"
#include "IDrawable.h"
#include "IShaderProperty.h"
#include "IGUIWidget.h"
#include "primitives/Line.h"
#include "primitives/Plane.h"
#include "primitives/Cuboid.h"
#include "primitives/Cubemap.h"
#include "../utilities/Window.h"
#include "../rendering/primitives/Cubemap.h"
#include "../cbs/components/Camera.h"

void zephyr::rendering::DrawManager::Initialize() {
    INFO_LOG(Logger::ESender::Rendering, "Initializing draw manager");

    // Dear imgui initialiation
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Engine::Instance().GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Load default font
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    // Create default shader programs
    {auto [it, vld] = m_Shaders.try_emplace("PureColor", "PureColor");
    if (vld) {
        it->second.AttachShaders("../../include/Zephyr3D/rendering/shaders/PureColorVert.glsl", "../../include/Zephyr3D/rendering/shaders/PureColorFrag.glsl");
        it->second.Traits(ShaderProgram::ETrait::Position | ShaderProgram::ETrait::Color);
    } else {
        ERROR_LOG(Logger::ESender::Rendering, "Failed to create PureColor shader\n");
    }}

    {auto [it, vld] = m_Shaders.try_emplace("PureTexture", "PureTexture");
    if (vld) {
        it->second.AttachShaders("../../include/Zephyr3D/rendering/shaders/PureTextureVert.glsl", "../../include/Zephyr3D/rendering/shaders/PureTextureFrag.glsl");
        it->second.Traits(ShaderProgram::ETrait::Position | ShaderProgram::ETrait::TexCoord);
    } else {
        ERROR_LOG(Logger::ESender::Rendering, "Failed to create PureTexture shader\n");
    }}

    {auto [it, vld] = m_Shaders.try_emplace("Phong", "Phong");
    if (vld) {
        it->second.AttachShaders("../../include/Zephyr3D/rendering/shaders/PhongVert.glsl", "../../include/Zephyr3D/rendering/shaders/PhongFrag.glsl");
        it->second.Traits(ShaderProgram::ETrait::Position | ShaderProgram::ETrait::Normal | ShaderProgram::ETrait::TexCoord);
    } else {
        ERROR_LOG(Logger::ESender::Rendering, "Failed to create Phong shader\n");
    }}

    {auto [it, vld] = m_Shaders.try_emplace("Skybox", "Skybox");
    if (vld) {
        it->second.AttachShaders("../../include/Zephyr3D/rendering/shaders/SkyboxVert.glsl", "../../include/Zephyr3D/rendering/shaders/SkyboxFrag.glsl");
        it->second.Traits(ShaderProgram::ETrait::Position);
    } else {
        ERROR_LOG(Logger::ESender::Rendering, "Failed to create Skybox shader\n");
    }}

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void zephyr::rendering::DrawManager::RegisterCamera(ICamera *camera) {
    m_Camera = camera;
}

zephyr::rendering::ICamera* zephyr::rendering::DrawManager::MainCamera() const {
    return m_Camera;
}

void zephyr::rendering::DrawManager::Skybox(const RawTexture& right, const RawTexture& left, const RawTexture& top, const RawTexture& bottom, const RawTexture& back, const RawTexture& front) {
    m_Skybox = std::make_unique<Cubemap>(right, left, top, bottom, back, front);
}

void zephyr::rendering::DrawManager::Background(const glm::vec3& background) {
    m_Background = background;
}

void zephyr::rendering::DrawManager::RegisterDrawCall(const IDrawable* drawable, const std::string& shader_name) {
    m_Shaders.at(shader_name).RegisterDrawCall(drawable);
}

void zephyr::rendering::DrawManager::UnregisterDrawCall(const IDrawable* drawable, const std::string& shader_name) {
    m_Shaders.at(shader_name).UnregisterDrawCall(drawable);
}

void zephyr::rendering::DrawManager::RegisterShaderProperty(const IShaderProperty* property, const std::string& shader_name) {
    m_Shaders.at(shader_name).RegisterShaderProperty(property);
}

void zephyr::rendering::DrawManager::UnregisterShaderProperty(const IShaderProperty* property, const std::string& shader_name) {
    m_Shaders.at(shader_name).UnregisterShaderProperty(property);
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

// TODO optimise 
void zephyr::rendering::DrawManager::DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
    m_NextFrameDraws.push(new Line(start, end, color));
}

// TODO optimise
void zephyr::rendering::DrawManager::DrawPlane(glm::mat4 model, glm::vec3 color) {
    m_NextFrameDraws.push(new Plane(model, color));
}

// TODO optimise
void zephyr::rendering::DrawManager::DrawCuboid(glm::mat4 model, glm::vec3 color) {
    m_NextFrameDraws.push(new Cuboid(model, color));
}

// TODO optimise
void zephyr::rendering::DrawManager::DrawSphere(glm::mat4 model, glm::vec3 color) {

}

void zephyr::rendering::DrawManager::CallDraws() {
    glClearColor(m_Background.x, m_Background.y, m_Background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 pv = m_Camera->Projection() * m_Camera->View();

    // Call draws in all shaders
    for (auto it = m_Shaders.begin(); it != m_Shaders.end(); it++) {
        auto& shader = it->second;

        shader.Use();

        shader.Uniform("pv", pv);
        shader.Uniform("viewPos", m_Camera->Position());

        shader.CallProperties();
        shader.CallDraws();
    }

    // Call one-frame draws
    auto& pure_color_shader = m_Shaders.at("PureColor");
    pure_color_shader.Use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!m_NextFrameDraws.empty()) {
        m_NextFrameDraws.top()->Draw(pure_color_shader);

        delete m_NextFrameDraws.top();
        m_NextFrameDraws.pop();
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Draw skybox
    if (m_Skybox != nullptr) {
        glDepthFunc(GL_LEQUAL);
        const ShaderProgram& skybox_shader = m_Shaders.at("Skybox");

        skybox_shader.Use();
        skybox_shader.Uniform("pv", m_Camera->Projection() * glm::mat4(glm::mat3(m_Camera->View())));

        m_Skybox->Draw(skybox_shader);

        glDepthFunc(GL_LESS);
    }

    // TODO: Dear ImGui
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
    glfwSwapBuffers(zephyr::Engine::Instance().GetWindow());
}
