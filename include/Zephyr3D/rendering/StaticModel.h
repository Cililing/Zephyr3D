#ifndef StaticModel_h
#define StaticModel_h

#include "Texture.h"
#include "../resources/Model.h"
#include "../resources/Mesh.h"

#include <vector>

namespace zephyr::rendering {

class StaticModel {
public:
    class StaticMesh {
    public:
        explicit StaticMesh(const resources::Mesh& raw_mesh);

        StaticMesh() = delete;
        StaticMesh(const StaticMesh&) = delete;
        StaticMesh& operator=(const StaticMesh&) = delete;
        StaticMesh(StaticMesh&& other) noexcept;
        StaticMesh& operator=(StaticMesh&& other) noexcept;
        ~StaticMesh();

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

    explicit StaticModel(const resources::Model& raw_model);

    StaticModel() = delete;
    StaticModel(const StaticModel&) = delete;
    StaticModel& operator=(const StaticModel&) = delete;
    StaticModel(StaticModel&&) = default;
    StaticModel& operator=(StaticModel&&) = default;
    ~StaticModel() = default;

    const std::vector<StaticModel::StaticMesh>& Meshes() const { return m_Meshes; }

private:
    std::vector<StaticModel::StaticMesh> m_Meshes;
};

}

#endif
