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

    virtual glm::mat4 View() const = 0;
    virtual glm::mat4 Projection() const = 0;
    virtual glm::vec3 LocalPosition() const = 0;
};

}

#endif
