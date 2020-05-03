#ifndef ResourcesManager_h
#define ResourcesManager_h

#include "Image.h"
#include "RawModel/RawModel.h"
#include "Sound.h"
#include "../debuging/Logger.h"

#include <string>
#include <unordered_map>

namespace zephyr::resources {

constexpr const char* ERROR_TEXTURE_PATH = "../../assets/textures/ErrorTexture.png";
constexpr const char* ERROR_MODEL3D_PATH = "../../assets/models/ErrorMesh/ErrorMesh.obj";
constexpr const char* RESOURCES_PATH_PREFIX = "../../assets/";

class ResourcesManager {
public:
    Image& LoadImage(std::string path);
    RawModel& LoadModel(std::string path);
    AudioClip& LoadAudioClip(std::string path);

private:
    std::unordered_map<std::string, Image> m_Textures;
    std::unordered_map<std::string, RawModel> m_Models;
    std::unordered_map<std::string, AudioClip> m_Sounds;
};

}

#endif 
