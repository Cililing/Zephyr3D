#include "ResourcesManager.h"

zephyr::resources::Image& zephyr::resources::ResourcesManager::LoadImage(std::string path) {
    path = RESOURCES_PATH_PREFIX + path;

    if (m_Textures.find(path) == m_Textures.end()) {
        m_Textures.try_emplace(path, path);
    }

    return m_Textures.at(path);
}

zephyr::resources::RawModel& zephyr::resources::ResourcesManager::LoadModel(std::string path) {
    path = RESOURCES_PATH_PREFIX + path;

    if (m_Models.find(path) == m_Models.end()) {
        m_Models.try_emplace(path, path, *this);
    }

    return m_Models.at(path);
}

zephyr::resources::AudioClip& zephyr::resources::ResourcesManager::LoadAudioClip(std::string path) {
    path = RESOURCES_PATH_PREFIX + path;

    if (m_Sounds.find(path) == m_Sounds.end()) {
        m_Sounds.try_emplace(path, path);
    }

    return m_Sounds.at(path);
}
