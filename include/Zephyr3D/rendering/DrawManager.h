#ifndef DrawManager_h
#define DrawManager_h

#include "shaders/CommonShaders.h"
#include "Cubemap.h"

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

class zephyr::resources::Image;

namespace zephyr::rendering {

class ICamera;
class IDrawable;
class IShaderProperty;
class IGUIWidget;

class DrawManager {
public:
    void Initialize();

    void RegisterCamera(ICamera* camera);
    ICamera* MainCamera() const;

    void Skybox(const resources::Image& right, const resources::Image& left, const resources::Image& top, const resources::Image& bottom, const resources::Image& back, const resources::Image& front);
    void Background(const glm::vec3& background);

    void RegisterDrawCall(const IDrawable* drawable, const std::string& shader_name);
    void UnregisterDrawCall(const IDrawable* drawable, const std::string& shader_name);

    void RegisterShaderProperty(const IShaderProperty* property, const std::string& shader_name);
    void UnregisterShaderProperty(const IShaderProperty* property, const std::string& shader_name);

    void RegisterGUIWidget(IGUIWidget* widget);
    void UnregisterGUIWidget(IGUIWidget* widget);

    void CallDraws();

    ShaderProgram* Shader(const std::string& name);

private:
    glm::vec3 m_Background{ 0.0f };
    std::unique_ptr<Cubemap> m_Skybox{ nullptr };

    Debug m_DebugShader;
    class Skybox m_SkyboxShader;
    ICamera* m_Camera{ nullptr };
    std::map<std::string, std::unique_ptr<ShaderProgram>> m_Shaders;
    std::vector<IGUIWidget*> m_GUIWidgets;
};

}

#endif
