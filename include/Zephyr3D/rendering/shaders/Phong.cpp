#include "Phong.h"
#include "../ICamera.h"
#include "../IRenderListener.h"
#include "../Texture.h"
#include "../../resources/Model.h"
#include "../../resources/Mesh.h"


zephyr::rendering::Phong::StaticModel::StaticModel(const resources::Model& raw_model) {
    m_StaticMeshes.reserve(raw_model.RawMeshes().size());
    for (auto it = raw_model.RawMeshes().begin(); it != raw_model.RawMeshes().end(); it++) {
        m_StaticMeshes.emplace_back(*it);
    }
}

void zephyr::rendering::Phong::StaticModel::Draw(const ShaderProgram& shader) const {
    shader.Uniform("model", m_Model);
    for (auto it = m_StaticMeshes.begin(); it != m_StaticMeshes.end(); it++) {
        it->Draw(shader);
    }
}

void zephyr::rendering::Phong::StaticModel::ModelMatrix(const glm::mat4& matrix_model) {
    m_Model = matrix_model;
}

glm::mat4 zephyr::rendering::Phong::StaticModel::ModelMatrix() const {
    return m_Model;
}


zephyr::rendering::Phong::StaticModel::StaticMesh::StaticMesh(const resources::Mesh& raw_mesh)
    : m_IndicesCount(raw_mesh.Indices().size())
    , m_Shininess(static_cast<float>(raw_mesh.Shininess())) {
    if (raw_mesh.Diffuse()) {
        m_Diffuse = std::make_unique<Texture>(*raw_mesh.Diffuse(), Texture::EType::Diffuse);
    }

    if (raw_mesh.Specular()) {
        m_Specular = std::make_unique<Texture>(*raw_mesh.Specular(), Texture::EType::Specular);
    }

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, raw_mesh.Vertices().size() * sizeof(resources::Mesh::Vertex), &raw_mesh.Vertices()[0], GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(resources::Mesh::Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal vectors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(resources::Mesh::Vertex), (void*)offsetof(resources::Mesh::Vertex, resources::Mesh::Vertex::Normal));
    glEnableVertexAttribArray(1);

    // Image coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(resources::Mesh::Vertex), (void*)offsetof(resources::Mesh::Vertex, resources::Mesh::Vertex::TexCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesCount * sizeof(unsigned int), &raw_mesh.Indices()[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

zephyr::rendering::Phong::StaticModel::StaticMesh::StaticMesh(StaticMesh&& other) noexcept
    : m_VAO(std::exchange(other.m_VAO, 0))
    , m_VBO(std::exchange(other.m_VBO, 0))
    , m_EBO(std::exchange(other.m_EBO, 0))
    , m_Diffuse(std::move(other.m_Diffuse))
    , m_Specular(std::move(other.m_Specular)) {
    m_IndicesCount = other.m_IndicesCount;
    m_Shininess = other.m_Shininess;
}

zephyr::rendering::Phong::StaticModel::StaticMesh& zephyr::rendering::Phong::StaticModel::StaticMesh::operator=(StaticMesh&& other) noexcept {
    m_VAO = std::exchange(other.m_VAO, 0);
    m_VBO = std::exchange(other.m_VBO, 0);
    m_EBO = std::exchange(other.m_EBO, 0);
    m_Diffuse = std::move(other.m_Diffuse);
    m_Specular = std::move(other.m_Diffuse);
    m_IndicesCount = other.m_IndicesCount;
    m_Shininess = other.m_Shininess;

    return *this;
}

zephyr::rendering::Phong::StaticModel::StaticMesh::~StaticMesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void zephyr::rendering::Phong::StaticModel::StaticMesh::Draw(const ShaderProgram& shader) const {
    if (m_Diffuse) {
        glActiveTexture(GL_TEXTURE0);
        shader.Uniform("material.diffuse", 0);
        glBindTexture(GL_TEXTURE_2D, m_Diffuse->ID());
    }

    if (m_Specular) {
        glActiveTexture(GL_TEXTURE1);
        shader.Uniform("material.specular", 1);
        glBindTexture(GL_TEXTURE_2D, m_Specular->ID());
    }

    shader.Uniform("material.shininess", m_Shininess);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

zephyr::rendering::Phong::Phong()
    : ShaderProgram(
    "Phong",
    ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongVert.glsl"),
    ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongFrag.glsl"),
    "") {
    m_SpotLights.reserve(m_MaxSpotLights);
    m_PointLights.reserve(m_MaxPointLights);
}

void zephyr::rendering::Phong::Draw(const ICamera* camera) {
    glm::mat4 pv = camera->Projection() * camera->View();

    Uniform("directionalLight.direction", m_DirectionalLight.Direction);
    Uniform("directionalLight.ambient", m_DirectionalLight.Ambient);
    Uniform("directionalLight.diffuse", m_DirectionalLight.Diffuse);
    Uniform("directionalLight.specular", m_DirectionalLight.Specular);

    for (size_t i = 0; i < m_NextSpotLightIndex; i++) {
        
    }

    for (size_t i = 0; i < m_NextPointLightIndex; i++) {
        
    }

    Uniform("pv", pv);
    Uniform("viewPosition", camera->LocalPosition());

    for (auto& drawable : m_Drawables) {
        auto user_pointer = static_cast<IRenderListener*>(drawable->UserPointer());
        user_pointer->OnDrawObject();
        drawable->Draw(*this);
    }
}

void zephyr::rendering::Phong::SetDirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) {
    m_DirectionalLight.Direction = direction;
    m_DirectionalLight.Ambient = ambient;
    m_DirectionalLight.Diffuse = diffuse;
    m_DirectionalLight.Specular = specular;
}

void zephyr::rendering::Phong::Register(StaticModel* static_model) {
    assert(std::find(m_Drawables.begin(), m_Drawables.end(), static_model) == m_Drawables.end());
    m_Drawables.push_back(static_model);
}

void zephyr::rendering::Phong::Unregister(StaticModel* static_mocel) {
    auto to_erase = std::find(m_Drawables.begin(), m_Drawables.end(), static_mocel);
    if (to_erase != m_Drawables.end()) {
        m_Drawables.erase(to_erase);
    }
}
