#ifndef Phong_h
#define Phong_h

#include "../ShaderProgram.h"
#include "../IDrawable.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/scene.h>
#pragma warning(pop)

#include <vector>
#include <optional>

namespace zephyr::resources {
    class Model;
    class Mesh;
}

namespace zephyr::rendering {

class Texture;
class IRenderListener;

class Phong : public ShaderProgram {
    const size_t MAX_POINTLIGHTS = 4;
    const size_t MAX_SPOTLIGHTS = 4;

public:
    class StaticModel;

    struct DirectionalLight {
        glm::vec3 Direction{ 0.0f };
        glm::vec3 Ambient{ 0.0f };
        glm::vec3 Diffuse{ 0.0f };
        glm::vec3 Specular{ 0.0f };
    };

    struct PointLight {
        glm::vec3 Position{ 0.0f };
        float Constant{ 1.0f };
        float Linear{ 0.0f };
        float Quadratic{ 0.0f };
        glm::vec3 Ambient{ 0.0f };
        glm::vec3 Diffuse{ 0.0f };
        glm::vec3 Specular{ 0.0f };
    };

    struct SpotLight {
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

    Phong();
    Phong(const Phong&) = delete;
    Phong& operator=(const Phong&) = delete;
    Phong(Phong&&) = delete;
    Phong& operator=(Phong&&) = delete;
    ~Phong() = default;

    void Draw(const ICamera* camera) override;

    DirectionalLight* CreateDirectionalLight();
    void DestroyDirectionalLight();
    PointLight* CreatePointLight();
    void DestroyPointLight(const PointLight* light);
    SpotLight* CreateSpotLight();
    void DestroySpotLight(const SpotLight* light);

    void Register(StaticModel* static_model);
    void Unregister(StaticModel* static_mocel);

private:
    std::vector<StaticModel*> m_Drawables;

    DirectionalLight m_DirectionalLight;
    std::vector<std::pair<bool /*is used*/, PointLight /*light struct*/>> m_PointLights{ MAX_POINTLIGHTS };
    std::vector<std::pair<bool /*is used*/, SpotLight /*light struct*/>> m_SpotLights{ MAX_POINTLIGHTS };
};


class Phong::StaticModel : public IDrawable {
public:
    class Mesh {
    public:
        Mesh(const aiMesh& mesh, const aiScene& scene, const std::string& directory, const aiMatrix4x4& transform);

        Mesh() = delete;
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;
        ~Mesh();

        void Draw(const ShaderProgram& shader, const glm::mat4& model) const;

    private:
        GLuint m_VAO;

        // Buffer objects
        GLuint m_Positions;
        GLuint m_Normals;
        GLuint m_TextureCoords;

        GLuint m_EBO;
        GLsizei m_IndicesCount;
        std::unique_ptr<Texture> m_Diffuse{ nullptr };
        std::unique_ptr<Texture> m_Specular{ nullptr };
        float m_Shininess;

        glm::mat4 m_Transform;
    };

    StaticModel(const aiScene& raw_model, const std::string& directory);

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
    std::vector<StaticModel::Mesh> m_StaticMeshes;
    glm::mat4 m_Model{0.0f};

    void LoadNode(const aiNode& node, const aiScene& scene, const std::string& directory, const aiMatrix4x4& transform);
};

}

#endif
