#ifndef Model_h
#define Model_h

#include "Mesh.h"

#pragma warning(push, 0)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

namespace zephyr::resources {

class ResourcesManager;
class Image;

class Model {
public:
    Model(const std::string& path, ResourcesManager& manager);

    Model() = delete;
    Model(const Model&) = default;
    Model& operator=(const Model&) = default;
    Model(Model&&) = default;
    Model& operator=(Model&&) = default;
    ~Model() = default;

    const std::string& Path() const { return m_Path; }
    const std::vector<Mesh>& RawMeshes() const { return m_Meshes; }

    void Skin(const Image* diffuse, const Image* specular, float shininess);

private:
    std::string m_Path;
    std::vector<Mesh> m_Meshes;

    void LoadNode(const aiNode* node, const aiScene* scene, const std::string& directory, ResourcesManager& manager);
    void LoadMesh(const aiMesh* mesh, const aiScene* scene, const std::string& directory, ResourcesManager& manager);
};

}

#endif
