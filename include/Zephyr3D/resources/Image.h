#ifndef Image_h
#define Image_h

#pragma warning(push, 0)
#include <stb_image.h>
#pragma warning(pop)

#include <iostream>
#include <string>

namespace zephyr::resources {

class Image {
public:
    explicit Image(const std::string& path);

    Image() = delete;
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;
    Image(Image&&) = delete;
    Image& operator=(Image&&) = delete;
    ~Image();

    unsigned char* Data() const { return m_Data; }
    int Width() const { return m_Width; }
    int Height() const { return m_Height; }
    int Components() const { return m_Components; }

private:
    unsigned char* m_Data;
    int m_Width;
    int m_Height;
    int m_Components;
    std::string m_Path;
};

}

#endif
