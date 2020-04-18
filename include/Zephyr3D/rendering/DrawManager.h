#ifndef DrawManager_h
#define DrawManager_h

#include "ShaderProgram.h"
#include "ICamera.h"
#include "IDrawable.h"
#include "IShaderProperty.h"
#include "IGUIWidget.h"
#include "Cubemap.h"
#include "shaders/CommonShaders.h"

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

class DrawManager {
public:
    void Initialize();

    void RegisterCamera(ICamera* camera);
    ICamera* MainCamera() const;

    void Skybox(const RawTexture& right, const RawTexture& left, const RawTexture& top, const RawTexture& bottom, const RawTexture& back, const RawTexture& front);
    void Background(const glm::vec3& background);

    void RegisterDrawCall(const IDrawable* drawable, const std::string& shader_name);
    void UnregisterDrawCall(const IDrawable* drawable, const std::string& shader_name);

    void RegisterShaderProperty(const IShaderProperty* property, const std::string& shader_name);
    void UnregisterShaderProperty(const IShaderProperty* property, const std::string& shader_name);

    void RegisterGUIWidget(IGUIWidget* widget);
    void UnregisterGUIWidget(IGUIWidget* widget);

    void CallDraws();

    void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);
    void DrawCuboid(glm::mat4 transform, glm::vec3 color);

private:
    glm::vec3 m_Background{ 0.0f };
    std::unique_ptr<Cubemap> m_Skybox{ nullptr };

    ICamera* m_Camera{ nullptr };
    std::map<std::string, std::unique_ptr<ShaderProgram>> m_Shaders;
    class Skybox m_SkyboxShader;
    Debug m_DebugShader;
    std::vector<IGUIWidget*> m_GUIWidgets;
};

}

#endif
