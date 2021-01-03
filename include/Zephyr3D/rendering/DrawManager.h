#ifndef DrawManager_h
#define DrawManager_h

#include "IDrawManager.h"
#include "shaders/SkyboxShader.h"
#include "shaders/DebugShader.h"

#pragma warning(push, 0)
#include <imgui.h>
#include "../dependencies/imgui_impl_opengl3.h"
#include "../dependencies/imgui_impl_glfw.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <assert.h>

namespace zephyr::rendering {

class DrawManager : public IDrawManager {
public:
    void Initialize();
    void Destroy();

    void RegisterCamera(ICamera* camera) override;
    ICamera* MainCamera() const override;

    void ClearColor(const glm::vec3& background);
    glm::vec3 ClearColor() const override;

    void RegisterGUIWidget(IGUIWidget* widget) override;
    void UnregisterGUIWidget(IGUIWidget* widget) override;

    void CallDraws();

    ShaderProgram* Shader(const std::string& name) override;

private:
    glm::vec3 m_Background{ 0.0f };

    Debug m_DebugShader;
    SkyboxShader m_SkyboxShader;
    ICamera* m_Camera{ nullptr };
    std::map<std::string, std::unique_ptr<ShaderProgram>> m_Shaders;
    std::vector<IGUIWidget*> m_GUIWidgets;
};

}

#endif
