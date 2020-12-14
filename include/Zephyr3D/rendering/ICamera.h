#ifndef ICamera_h
#define ICamera_h

#include <glm/glm.hpp>

namespace zephyr::rendering {

class ICamera {
public:
    ICamera() = default;
    ICamera(const ICamera&) = delete;
    ICamera& operator=(const ICamera&) = delete;
    ICamera(ICamera&&) = delete;
    ICamera& operator=(ICamera&&) = delete;

    virtual glm::mat4 View() = 0;
    virtual glm::mat4 Projection() = 0;
    virtual glm::vec3 LocalPosition() = 0;
};

}

#endif
