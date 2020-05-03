#include "StaticModel.h"

zephyr::rendering::StaticModel::StaticModel(const resources::Model& raw_model) {
    m_Meshes.reserve(raw_model.RawMeshes().size());

    for (auto it = raw_model.RawMeshes().begin(); it != raw_model.RawMeshes().end(); it++) {
        m_Meshes.emplace_back(*it);
    }
}

zephyr::rendering::StaticModel::StaticMesh::StaticMesh(const resources::Mesh& raw_mesh)
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

zephyr::rendering::StaticModel::StaticMesh::~StaticMesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

zephyr::rendering::StaticModel::StaticMesh::StaticMesh(StaticMesh&& other) noexcept
    : m_VAO(std::exchange(other.m_VAO, 0))
    , m_VBO(std::exchange(other.m_VBO, 0))
    , m_EBO(std::exchange(other.m_EBO, 0))
    , m_Diffuse(std::move(other.m_Diffuse))
    , m_Specular(std::move(other.m_Specular)) {
    m_IndicesCount = other.m_IndicesCount;
    m_Shininess = other.m_Shininess;
}

zephyr::rendering::StaticModel::StaticMesh& zephyr::rendering::StaticModel::StaticMesh::operator=(StaticMesh&& other) noexcept {
    m_VAO = std::exchange(other.m_VAO, 0);
    m_VBO = std::exchange(other.m_VBO, 0);
    m_EBO = std::exchange(other.m_EBO, 0);
    m_Diffuse = std::move(other.m_Diffuse);
    m_Specular = std::move(other.m_Diffuse);
    m_IndicesCount = other.m_IndicesCount;
    m_Shininess = other.m_Shininess;

    return *this;
}