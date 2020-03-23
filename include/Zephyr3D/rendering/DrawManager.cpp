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

void DrawManager::Initialize() {
    INFO_LOG(Logger::ESender::Rendering, "Initializing draw manager");

    // TODO: Dear ImGui
    // Dear imgui initialiation
    /*ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Engine::Instance().GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Load default font
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();*/

    // Create shader programs
    m_ShaderPrograms[static_cast<size_t>(EShaderType::PureColor)].AttachShaders("../../include/Zephyr3D/shaders/PURE_COLOR.vert",
                                                                                "../../include/Zephyr3D/shaders/PURE_COLOR.frag");


    m_ShaderPrograms[static_cast<size_t>(EShaderType::PureTexture)].AttachShaders("../../include/Zephyr3D/shaders/PURE_TEXTURE.vert",
                                                                                  "../../include/Zephyr3D/shaders/PURE_TEXTURE.frag");


    m_ShaderPrograms[static_cast<size_t>(EShaderType::Phong)].AttachShaders("../../include/Zephyr3D/shaders/PHONG.vert",
                                                                            "../../include/Zephyr3D/shaders/PHONG.frag");
    m_ShaderPrograms[static_cast<size_t>(EShaderType::Phong)].Traits(ShaderProgram::ETrait::LIGHT_RECEIVER);


    m_ShaderPrograms[static_cast<size_t>(EShaderType::Skybox)].AttachShaders("../../include/Zephyr3D/shaders/SKYBOX.vert",
                                                                             "../../include/Zephyr3D/shaders/SKYBOX.frag");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void DrawManager::RegisterCamera(Camera *camera) {
    m_Camera = camera;
}

Camera* DrawManager::MainCamera() const {
    return m_Camera;
}

void DrawManager::Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front) {
    m_Skybox = std::make_unique<Cubemap>(right, left, top, bottom, back, front);
}

void DrawManager::Background(const glm::vec3& background) {
    m_Background = background;
}

void DrawManager::RegisterDrawCall(const IDrawable* drawable, EShaderType shader) {
    m_ShaderPrograms[static_cast<size_t>(shader)].RegisterDrawCall(drawable);
}

void DrawManager::UnregisterDrawCall(const IDrawable* drawable, EShaderType shader) {
    m_ShaderPrograms[static_cast<size_t>(shader)].UnregisterDrawCall(drawable);
}

void DrawManager::RegisterShaderProperty(const IShaderProperty* property, EShaderType shader) {
    m_ShaderPrograms[static_cast<size_t>(shader)].RegisterShaderProperty(property);
}

void DrawManager::UnregisterShaderProperty(const IShaderProperty* property, EShaderType shader) {
    m_ShaderPrograms[static_cast<size_t>(shader)].UnregisterShaderProperty(property);
}

void DrawManager::RegisterGUIWidget(IGUIWidget* widget) {
    // Ensure that each widget is registered at most once
    assert(std::find(m_GUIWidgets.begin(), m_GUIWidgets.end(), widget) == m_GUIWidgets.end());

    m_GUIWidgets.push_back(widget);
}

void DrawManager::UnregisterGUIWidget(IGUIWidget* widget) {
    // Unregistering not registered widget has no effect
    auto to_erase = std::find(m_GUIWidgets.begin(), m_GUIWidgets.end(), widget);
    if (to_erase != m_GUIWidgets.end()) {
        m_GUIWidgets.erase(to_erase);
    }
}

// TODO optimise 
void DrawManager::DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
    m_NextFrameDraws.push(new Line(start, end, color));
}

// TODO optimise
void DrawManager::DrawPlane(glm::mat4 model, glm::vec3 color) {
    m_NextFrameDraws.push(new Plane(model, color));
}

// TODO optimise
void DrawManager::DrawCuboid(glm::mat4 model, glm::vec3 color) {
    m_NextFrameDraws.push(new Cuboid(model, color));
}

// TODO optimise
void DrawManager::DrawSphere(glm::mat4 model, glm::vec3 color) {

}

void DrawManager::CallDraws() {
    glClearColor(m_Background.x, m_Background.y, m_Background.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 pv = m_Camera->Projection() * m_Camera->ViewMatrix();

    // Call draws in all shaders
    for (auto shader = m_ShaderPrograms.begin(); shader != m_ShaderPrograms.end(); shader++) {
        shader->Use();

        shader->Uniform("pv", pv);
        shader->Uniform("viewPos", m_Camera->Object().Root().Position());

        shader->CallProperties();
        shader->CallDraws();
    }

    // Call one-frame draws
    auto& pure_color_shader = m_ShaderPrograms[static_cast<size_t>(EShaderType::PureColor)];
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
        const ShaderProgram& skybox_shader = m_ShaderPrograms[static_cast<size_t>(EShaderType::Skybox)];

        skybox_shader.Use();
        skybox_shader.Uniform("pv", m_Camera->Projection() * glm::mat4(glm::mat3(m_Camera->ViewMatrix())));

        m_Skybox->Draw(skybox_shader);

        glDepthFunc(GL_LESS);
    }

    // TODO: Dear ImGui
    // Draw GUI
    /*ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (auto widget = m_GUIWidgets.begin(); widget != m_GUIWidgets.end(); widget++) {
        (*widget)->Draw();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();*/

    // End of drawing
    glfwSwapBuffers(Engine::Instance().GetWindow());
}
