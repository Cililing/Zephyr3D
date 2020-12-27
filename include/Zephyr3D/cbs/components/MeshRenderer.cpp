#include "MeshRenderer.h"
#include "Transform.h"
#include "../../rendering/IDrawable.h"
#include "../../rendering/shaders/Phong.h"

zephyr::cbs::MeshRenderer::MeshRenderer(class Object& object, ID_t id, const resources::Model& raw_model, const std::string& shader_name)
    : Component(object, id)
    , m_Model(new rendering::Phong::StaticModel(raw_model))
    , m_ShaderName(shader_name) {

    m_Model->UserPointer(static_cast<IRenderListener*>(this));
}

void zephyr::cbs::MeshRenderer::Initialize() {
    assert(TransformIn.Connected());

    Object().Scene().GetDrawManager().RegisterDrawCall(m_Model, "Phong");
}

void zephyr::cbs::MeshRenderer::Destroy() {
    Object().Scene().GetDrawManager().UnregisterDrawCall(m_Model, "Phong");
}

void zephyr::cbs::MeshRenderer::OnDrawObject() {
    std::cout << "On draw object\n";
}
