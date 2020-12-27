#ifndef MeshRenderer_h
#define MeshRenderer_h

#include "Component.h"
#include "../Object.h"
#include "../connections/PropertyIn.h"
#include "../../Scene.h"
#include "../../rendering/IRenderListener.h"

namespace zephyr::rendering {

class IDrawable;

}

namespace zephyr::cbs {

class Transform;

class MeshRenderer : public Component, public IRenderListener {
public:
    MeshRenderer(class Object& object, ID_t id, const resources::Model& model, const std::string& shader_name);

    void Initialize() override;
    void Destroy() override;

    void OnDrawObject() override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    rendering::IDrawable* m_Model;
    std::string m_ShaderName;
};

}

#endif
