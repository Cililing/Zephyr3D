#include "ResourcesManager.h"

#include "../core/debugging/Logger.h"

#include <assimp/postprocess.h>

#undef LoadImage

zephyr::resources::Image& zephyr::resources::ResourcesManager::LoadImage(std::string path) {
    if (m_Textures.find(path) == m_Textures.end()) {
        m_Textures.try_emplace(path, path);
    }

    return m_Textures.at(path);
}

const aiScene& zephyr::resources::ResourcesManager::LoadModel(const std::string& path) {
    const std::string full_path = ASSETS_PATH_PREFIX + path;

    if (m_Models2.find(full_path) == m_Models2.end()) {
        auto& importer = m_Models2[full_path];
        const aiScene* scene = importer.ReadFile(full_path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            ERROR_LOG(Logger::ESender::Rendering, "Failed to load model %s:\n%s", full_path.c_str(), importer.GetErrorString());
        }
    }

    return *m_Models2[full_path].GetScene();
}

