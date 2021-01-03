#ifndef Phong_h
#define Phong_h

#include "../ShaderProgram.h"
#include "../IDrawable.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning(pop)

#include <vector>

namespace zephyr::resources {
    class Model;
    class Mesh;
}

namespace zephyr::rendering {

class Texture;
class IRenderListener;

class Phong : public ShaderProgram {

    struct DirectionalLight {
        glm::vec3 Direction{ 0.0f };
        glm::vec3 Ambient{ 0.0f };
        glm::vec3 Diffuse{ 0.0f };
        glm::vec3 Specular{ 0.0f };
    };

    struct PointLight {
        size_t Index{ 0 };
        glm::vec3 Position{ 0.0f };
        float Constant{ 1.0f };
        float Linear{ 0.0f };
        float Quadratic{ 0.0f };
        glm::vec3 Ambient{ 0.0f };
        glm::vec3 Diffuse{ 0.0f };
        glm::vec3 Specular{ 0.0f };
    };

    struct SpotLight {
        size_t Index{ 0 };
        glm::vec3 Position{ 0.0f };
        glm::vec3 Direction{ 0.0f };
        float CutOff{ 0.0f };
        float OutterCutOff{ 0.0f };
        float Constant{ 0.0f };
        float Linear{ 0.0f };
        float Quadratic{ 0.0f };
        glm::vec3 Ambient{ 0.0f };
        glm::vec3 Diffuse{ 0.0f };
        glm::vec3 Specular{ 0.0f };
    };

public:
    class StaticModel;

    Phong();
    Phong(const Phong&) = delete;
    Phong& operator=(const Phong&) = delete;
    Phong(Phong&&) = delete;
    Phong& operator=(Phong&&) = delete;
    ~Phong() = default;

    void Draw(const ICamera* camera) override;

    void SetDirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    void Register(StaticModel* static_model);
    void Unregister(StaticModel* static_mocel);

private:
    std::vector<StaticModel*> m_Drawables;

    DirectionalLight m_DirectionalLight;
    size_t m_MaxSpotLights{ 1 };
    size_t m_NextSpotLightIndex{ 0 };
    std::vector<SpotLight> m_SpotLights;
    size_t m_MaxPointLights{ 4 };
    size_t m_NextPointLightIndex{ 0 };
    std::vector<PointLight> m_PointLights;
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

    void ModelMatrix(const glm::mat4& matrix_model);
    glm::mat4 ModelMatrix() const;

private:
    std::vector<StaticModel::StaticMesh> m_StaticMeshes;
    glm::mat4 m_Model{0.0f};
};

}

#endif
