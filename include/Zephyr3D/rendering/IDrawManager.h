#ifndef IDrawManager_h
#define IDrawManager_h

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning(pop)

#include <string>

namespace zephyr::resources {
    class Image;
}

namespace zephyr::rendering {

class ICamera;
class IDrawable;
class IShaderProperty;
class IGUIWidget;
class ShaderProgram;

class IDrawManager {
public:
    IDrawManager() = default;
    IDrawManager(const IDrawManager&) = delete;
    IDrawManager& operator=(const IDrawManager&) = delete;
    IDrawManager(IDrawManager&&) = delete;
    IDrawManager& operator=(IDrawManager&&) = delete;
    virtual ~IDrawManager() = default;

    virtual void RegisterCamera(ICamera* camera) = 0;
    virtual ICamera* MainCamera() const = 0;
    virtual void ClearColor(const glm::vec3& color) = 0;
    virtual glm::vec3 ClearColor() const = 0;
    virtual ShaderProgram* Shader(const std::string& name) = 0;
    virtual void RegisterGUIWidget(IGUIWidget* widget) = 0;
    virtual void UnregisterGUIWidget(IGUIWidget* widget) = 0;
};

}

#endif

