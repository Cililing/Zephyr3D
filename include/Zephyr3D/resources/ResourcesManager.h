#ifndef ResourcesManager_h
#define ResourcesManager_h

#include "Image.h"

#pragma warning(push, 0)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#pragma warning(pop)

#include <string>
#include <unordered_map>

#undef LoadImage

namespace zephyr::resources {

constexpr const char* ERROR_TEXTURE_PATH = "textures/TextureError.png";
constexpr const char* ERROR_MODEL3D_PATH = "models/MeshError/MeshError.obj";

constexpr const char* ASSETS_PATH_PREFIX = "../../assets/";

class ResourcesManager {
public:
    Image& LoadImage(std::string path);
    const aiScene& LoadModel(const std::string& path);

private:
    std::unordered_map<std::string, Image> m_Textures;
    std::unordered_map<std::string, Assimp::Importer> m_Models2;
};

}

#endif 
