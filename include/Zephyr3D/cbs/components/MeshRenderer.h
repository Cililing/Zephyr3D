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

class MeshRenderer : public Component, public rendering::IDrawable {
public:
    MeshRenderer(class Object& object, ID_t id, const resources::Model& model, const std::string& shader_name);

    void Initialize() override;
    void Destroy() override;

    void Draw(const rendering::ShaderProgram& shader) const override;

    PropertyIn<Transform*> TransformIn{ this };

private:
    void DrawMesh(const rendering::ShaderProgram& shader, const rendering::StaticModel::StaticMesh& mesh) const;

    rendering::StaticModel m_Model;
    std::string m_ShaderName;
};

}

#endif
