#ifndef DrawManager_h
#define DrawManager_h

#include "ShaderProgram.h"
#include "ICamera.h"
#include "IDrawable.h"
#include "IShaderProperty.h"
#include "IGUIWidget.h"
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

namespace zephyr::rendering {

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

    void RegisterCamera(ICamera* camera);
    ICamera* MainCamera() const;

    void Skybox(const RawTexture& right, const RawTexture& left, const RawTexture& top, const RawTexture& bottom, const RawTexture& back, const RawTexture& front);
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

    ICamera* m_Camera{ nullptr };
    std::array<ShaderProgram, static_cast<size_t>(EShaderType::Count)> m_ShaderPrograms;
    std::stack<IDrawable*> m_NextFrameDraws;
    std::vector<IGUIWidget*> m_GUIWidgets;
};

}

#endif
