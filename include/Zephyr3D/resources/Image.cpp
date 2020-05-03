#include "Image.h"
#include "ResourcesManager.h"

zephyr::resources::Image::Image(const std::string& path)
    : m_Path(ASSETS_PATH_PREFIX + path) {
    m_Data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Components, 0);
    if (!m_Data) {
        Logger::Instance().ErrorLog(Logger::ESender::Resources, __FILE__, __LINE__, "Failed to load image %s", path.c_str());

        std::string error_path(ASSETS_PATH_PREFIX);
        error_path.append(ERROR_TEXTURE_PATH);
        m_Data = stbi_load(error_path.c_str(), &m_Width, &m_Height, &m_Components, 0);
    }
}

zephyr::resources::Image::~Image() {
    stbi_image_free(m_Data);
}
