#include "MeshRenderer.h"
#include "Transform.h"
#include "../../rendering/IDrawable.h"


zephyr::cbs::MeshRenderer::MeshRenderer(class Object& object, ID_t id, const resources::Model& raw_model, const std::string& shader_name)
    : Component(object, id)
    , m_Model(raw_model)
    , m_ShaderName(shader_name) {

    m_Model.UserPointer(static_cast<IRenderListener*>(this));
}

void zephyr::cbs::MeshRenderer::Initialize() {
    assert(TransformIn.Connected());

    Object().Scene().GetDrawManager().RegisterDrawCall(&m_Model, "Phong");
}

void zephyr::cbs::MeshRenderer::Destroy() {
    Object().Scene().GetDrawManager().UnregisterDrawCall(&m_Model, "Phong");
}

void zephyr::cbs::MeshRenderer::OnDrawObject() {
    m_Model.ModelMatrix(TransformIn.Value()->Model());
}
