#ifndef Math_h
#define Math_h

#pragma warning(push, 0)
#include <glm/glm.hpp>

#include <bullet/LinearMath/btVector3.h>

#pragma warning(pop)

glm::vec3 Vector3(const btVector3& vector) {
    return glm::vec3(
        vector.getX(),
        vector.getY(),
        vector.getZ()
    );
}

btVector3 Vector3(const glm::vec3& vector) {
    return btVector3(
        vector.x,
        vector.y,
        vector.z
    );
}

#endif
