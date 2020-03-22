#ifndef DrawManager_h
#define DrawManager_h

#include "ShaderProgram.h"
#include "primitives/Cubemap.h"

#pragma warning(push, 0)
#include <imgui.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <iostream>
#include <stack>
#include <vector>
#include <array>
#include <assert.h>


class Camera;
class IDrawable;
class IShaderProperty;
class IGUIWidget;

enum class EShaderType {
    PureColor = 0,
    PureTexture,
    Phong,
    Skybox,

    Count
};

class DrawManager {
public:
    void Initialize();

    void RegisterCamera(Camera* camera);
    Camera* MainCamera() const;

    void Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    void Background(const glm::vec3& background);

    void RegisterDrawCall(const IDrawable* drawable, EShaderType shader);
    void UnregisterDrawCall(const IDrawable* drawable, EShaderType shader);

    void RegisterShaderProperty(const IShaderProperty* property, EShaderType shader);
    void UnregisterShaderProperty(const IShaderProperty* property, EShaderType shader);

    void RegisterGUIWidget(IGUIWidget* widget);
    void UnregisterGUIWidget(IGUIWidget* widget);

    void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color);
    void DrawPlane(glm::mat4 model, glm::vec3 color);
    void DrawCuboid(glm::mat4 model, glm::vec3 color);
    void DrawSphere(glm::mat4 model, glm::vec3 color);

    void CallDraws();

private:
    glm::vec3 m_Background{ 0.0f };
    std::unique_ptr<Cubemap> m_Skybox{ nullptr };

    Camera* m_Camera{ nullptr };
    std::array<ShaderProgram, static_cast<size_t>(EShaderType::Count)> m_ShaderPrograms;
    std::stack<IDrawable*> m_NextFrameDraws;
    std::vector<IGUIWidget*> m_GUIWidgets;
};

#endif
