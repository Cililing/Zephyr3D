#ifndef Phong_h
#define Phong_h

#include "../ShaderProgram.h"
#include "../IDrawable.h"

#include <vector>

namespace zephyr::resources {
    class Model;
    class Mesh;
}

namespace zephyr::rendering {

class Texture;

class Phong : public ShaderProgram {
public:
    class StaticModel;

    Phong()
        : ShaderProgram(
            "Phong",
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongFrag.glsl"),
            "") { }

    Phong(const Phong&) = delete;
    Phong& operator=(const Phong&) = delete;
    Phong(Phong&&) = delete;
    Phong& operator=(Phong&&) = delete;
    ~Phong() = default;

};

class Phong::StaticModel : public IDrawable {
public:
    class StaticMesh {
    public:
        explicit StaticMesh(const resources::Mesh& raw_StaticMesh);

        StaticMesh() = delete;
        StaticMesh(const StaticMesh&) = delete;
        StaticMesh& operator=(const StaticMesh&) = delete;
        StaticMesh(StaticMesh&& other) noexcept;
        StaticMesh& operator=(StaticMesh&& other) noexcept;
        ~StaticMesh();

        void Draw(const ShaderProgram& shader) const;

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

    void Draw(const ShaderProgram& shader) const override;

    const std::vector<StaticModel::StaticMesh>& StaticMeshes() const { return m_StaticMeshes; }

private:
    std::vector<StaticModel::StaticMesh> m_StaticMeshes;
};

}

#endif
