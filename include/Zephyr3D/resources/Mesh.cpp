#include "Mesh.h"

zephyr::resources::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const Image* diffuse, const Image* specular, float shininess)
    : m_Vertices(vertices)
    , m_Indices(indices)
    , m_Diffuse(diffuse)
    , m_Specular(specular)
    , m_Shininess(shininess) {
}
