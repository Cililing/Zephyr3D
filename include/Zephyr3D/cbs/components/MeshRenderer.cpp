#include "MeshRenderer.h"
#include "Transform.h"
#include "../Object.h"
#include "../../Scene.h"


zephyr::cbs::MeshRenderer::MeshRenderer(class Object& object, ID_t id, const aiScene& raw_model, const std::string& path)
    : Component(object, id)
    , m_Model(raw_model, path) {

    m_Model.UserPointer(static_cast<IRenderListener*>(this));
}

void zephyr::cbs::MeshRenderer::Initialize() {
    assert(TransformIn.Connected());

    static_cast<zephyr::rendering::Phong*>(Object().Scene().Rendering().Shader("Phong"))->Register(&m_Model);
}

void zephyr::cbs::MeshRenderer::Destroy() {
    static_cast<zephyr::rendering::Phong*>(Object().Scene().Rendering().Shader("Phong"))->Unregister(&m_Model);
}

zephyr::rendering::IDrawable* zephyr::cbs::MeshRenderer::DrawableHandle() {
    return &m_Model;
}

void zephyr::cbs::MeshRenderer::OnDrawObject() {
    m_Model.ModelMatrix(TransformIn.Value()->Model());
}
