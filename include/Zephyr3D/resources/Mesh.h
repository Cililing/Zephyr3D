#ifndef Mesh_h
#define Mesh_h

#include "Image.h"
#include "../rendering/ShaderProgram.h"

#pragma warning(push, 0)
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <vector>
#pragma warning(pop)

namespace zephyr::resources {

class Mesh {
public:
    struct Vertex {
        glm::vec3 Position{ 0.0f };
        glm::vec3 Normal{ 0.0f };
        glm::vec2 TexCoords{ 0.0f };
    };

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const Image* diffuse, const Image* specular, float shininess);

    Mesh() = delete;
    Mesh(const Mesh&) = default;
    Mesh& operator=(const Mesh&) = default;
    Mesh(Mesh&& other) = default;
    Mesh& operator=(Mesh&& other) = default;
    ~Mesh() = default;

    const std::vector<Vertex>& Vertices() const { return m_Vertices; }
    const std::vector<unsigned int>& Indices() const { return m_Indices; }

    const Image* Diffuse() const { return m_Diffuse; }
    void Diffuse(const Image* texture) { m_Diffuse = texture; }

    const Image* Specular() const { return m_Specular; }
    void Specular(const Image* texture) { m_Specular = texture; }

    float Shininess() const { return m_Shininess; }
    void Shininess(float shininess) { m_Shininess = shininess; }

private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    const Image* m_Diffuse;
    const Image* m_Specular;
    float m_Shininess;
};

}

#endif
