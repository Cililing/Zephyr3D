#include "MeshRenderer.h"
#include "Transform.h"

zephyr::cbs::MeshRenderer::MeshRenderer(class Object& object, ID_t id, const zephyr::resources::Model& raw_model, const std::string& shader_name)
    : Component(object, id)
    , m_Model(raw_model)
    , m_ShaderName(shader_name) {

}

void zephyr::cbs::MeshRenderer::Initialize() {
    Object().Scene().GetDrawManager().RegisterDrawCall(this, m_ShaderName);
}

void zephyr::cbs::MeshRenderer::Destroy() {
    Object().Scene().GetDrawManager().UnregisterDrawCall(this, m_ShaderName);
}

void zephyr::cbs::MeshRenderer::Draw(const zephyr::rendering::ShaderProgram& shader) const {
    shader.Uniform("model", TransformIn.Value()->Model());

    for (auto it = m_Model.Meshes().begin(); it != m_Model.Meshes().end(); it++) {
        DrawMesh(shader, *it);
    }
}

void zephyr::cbs::MeshRenderer::DrawMesh(const zephyr::rendering::ShaderProgram& shader, const zephyr::rendering::StaticModel::StaticMesh& mesh) const {
    if (mesh.Diffuse()) {
        glActiveTexture(GL_TEXTURE0);
        shader.Uniform("material.diffuse", 0);
        glBindTexture(GL_TEXTURE_2D, mesh.Diffuse()->ID());
    }

    if (mesh.Specular()) {
        glActiveTexture(GL_TEXTURE1);
        shader.Uniform("material.specular", 1);
        glBindTexture(GL_TEXTURE_2D, mesh.Specular()->ID());
    }

    shader.Uniform("material.shininess", mesh.Shininess());

    glBindVertexArray(mesh.VAO());
    glDrawElements(GL_TRIANGLES, mesh.IndicesCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}
