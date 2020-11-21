#ifndef MeshRenderer_h
#define MeshRenderer_h

#include "Component.h"
#include "../Object.h"
#include "../connections/PropertyIn.h"
#include "../../Scene.h"
#include "../../rendering/IDrawable.h"
#include "../../rendering/StaticModel.h"

namespace zephyr::cbs {

class Transform;

class MeshRenderer : public Component, public zephyr::rendering::IDrawable {
public:
    MeshRenderer(class Object& object, ID_t id, const zephyr::resources::Model& model, const std::string& shader_name);

    void Initialize() override;
    void Destroy() override;

    void Draw(const zephyr::rendering::ShaderProgram& shader) const override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    void DrawMesh(const zephyr::rendering::ShaderProgram& shader, const zephyr::rendering::StaticModel::StaticMesh& mesh) const;

    zephyr::rendering::StaticModel m_Model;
    std::string m_ShaderName;
};

}

#endif
