#ifndef Model_h
#define Model_h

#include "Texture.h"
#include "../resources/RawModel/RawModel.h"
#include "../resources/RawModel/RawMesh.h"

#include <vector>

namespace zephyr::rendering {

class Model {
public:
    class Mesh {
    public:
        explicit Mesh(const zephyr::resources::RawMesh& raw_mesh);

        Mesh() = delete;
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;
        ~Mesh();

        GLuint VAO() const { return m_VAO; }
        GLuint VBO() const { return m_VBO; }
        GLuint EBO() const { return m_EBO; }
        GLsizei IndicesCount() const { return m_IndicesCount; }
        const Texture* Diffuse() const { return m_Diffuse.get(); }
        const Texture* Specular() const { return m_Specular.get(); }
        float Shininess() const { return m_Shininess; }

    private:
        GLuint m_VAO;
        GLuint m_VBO;
        GLuint m_EBO;
        GLsizei m_IndicesCount;
        std::unique_ptr<Texture> m_Diffuse{ nullptr };
        std::unique_ptr<Texture> m_Specular{ nullptr };
        float m_Shininess;
    };

    explicit Model(const zephyr::resources::RawModel& raw_model);

    Model() = delete;
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&&) = default;
    Model& operator=(Model&&) = default;
    ~Model() = default;

    const std::vector<Model::Mesh>& Meshes() const { return m_Meshes; }

private:
    std::vector<Model::Mesh> m_Meshes;
};

}

#endif
