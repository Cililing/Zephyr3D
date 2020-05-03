#include "MeshRenderer.h"
#include "Transform.h"

MeshRenderer::MeshRenderer(zephyr::resources::Model& raw_model, const std::string& shader_name)
    : m_Model(raw_model)
    , m_ShaderName(shader_name) {
}

void MeshRenderer::Initialize() {
    Object().Scene().RegisterDrawCall(this, m_ShaderName);
}

void MeshRenderer::Destroy() {
    Object().Scene().UnregisterDrawCall(this, m_ShaderName);
}

void MeshRenderer::Draw(const zephyr::rendering::ShaderProgram& shader) const {
    shader.Uniform("model", TransformIn.Value()->Model());

    for (auto it = m_Model.Meshes().begin(); it != m_Model.Meshes().end(); it++) {
        DrawMesh(shader, *it);
    }
}

void MeshRenderer::DrawMesh(const zephyr::rendering::ShaderProgram& shader, const zephyr::rendering::StaticModel::StaticMesh& mesh) const {
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
