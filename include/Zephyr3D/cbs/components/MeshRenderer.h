#ifndef MeshRenderer_h
#define MeshRenderer_h

#include "Component.h"
#include "Transform.h"
#include "../connections/PropertyIn.h"
#include "../../rendering/IRenderListener.h"
#include "../../rendering/shaders/Phong.h"

namespace zephyr::cbs {

class Transform;

class MeshRenderer : public Component, public zephyr::rendering::IRenderListener {
public:
    MeshRenderer(class Object& object, ID_t id, const aiScene& raw_model, const std::string& path);

    void Initialize() override;
    void Destroy() override;

    zephyr::rendering::IDrawable* DrawableHandle() override;
    void OnDrawObject() override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    rendering::Phong::StaticModel m_Model;
    std::string m_ShaderName;
};

}

#endif
