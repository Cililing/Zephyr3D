#include "Image.h"
#include "ResourcesManager.h"

zephyr::resources::Image::Image(const std::string& path)
    : m_Path(path) {
    m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Components, 0);
    if (!m_Data) {
        Logger::Instance().ErrorLog(Logger::ESender::Resources, __FILE__, __LINE__, "Failed to load texture %s", path.c_str());
        m_Data = stbi_load(ERROR_TEXTURE_PATH, &m_Width, &m_Height, &m_Components, 0);
    }
}

zephyr::resources::Image::~Image() {
    stbi_image_free(m_Data);
}
