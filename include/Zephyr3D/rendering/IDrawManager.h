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
    virtual void Skybox(const resources::Image& right, const resources::Image& left, const resources::Image& top, const resources::Image& bottom, const resources::Image& back, const resources::Image& front) = 0;
    virtual void ClearColor(const glm::vec3& color) = 0;
    virtual glm::vec3 ClearColor() const = 0;
    virtual void RegisterDrawCall(const IDrawable* drawable, const std::string& shader_name) = 0;
    virtual void UnregisterDrawCall(const IDrawable* drawable, const std::string& shader_name) = 0;
    virtual void RegisterShaderProperty(const IShaderProperty* property, const std::string& shader_name) = 0;
    virtual void UnregisterShaderProperty(const IShaderProperty* property, const std::string& shader_name) = 0;
    virtual void RegisterGUIWidget(IGUIWidget* widget) = 0;
    virtual void UnregisterGUIWidget(IGUIWidget* widget) = 0;
};

}

#endif

