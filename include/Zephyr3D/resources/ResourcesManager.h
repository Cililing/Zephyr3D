#ifndef ResourcesManager_h
#define ResourcesManager_h

#include "Image.h"
#include "Model.h"
#include "AudioClip.h"
#include "../debuging/Logger.h"

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
    Model& LoadModel(std::string path);
    AudioClip& LoadAudioClip(std::string path);

private:
    std::unordered_map<std::string, Image> m_Textures;
    std::unordered_map<std::string, Model> m_Models;
    std::unordered_map<std::string, AudioClip> m_Sounds;
};

}

#endif 
