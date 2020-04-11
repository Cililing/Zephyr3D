#ifndef MeshRenderer_h
#define MeshRenderer_h

#pragma warning(disable: 26495)

#include "Component.h"
#include "../Object.h"
#include "../connections/PropertyIn.h"
#include "../../scenes/Scene.h"
#include "../../rendering/IDrawable.h"
#include "../../rendering/Model.h"

class Transform;
class MeshRenderer : public Component, public zephyr::rendering::IDrawable {
public:
    MeshRenderer(RawModel& model, const std::string& shader_name);

    void Initialize() override;
    void Destroy() override;

    void Draw(const zephyr::rendering::ShaderProgram& shader) const override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    void DrawMesh(const zephyr::rendering::ShaderProgram& shader, const zephyr::rendering::Model::Mesh& mesh) const;

    zephyr::rendering::Model m_Model;
    std::string m_ShaderName;
};

#pragma warning(default: 26495)
#endif
