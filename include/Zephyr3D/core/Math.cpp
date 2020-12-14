#include "Math.h"

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

glm::quat Quaternion(const btQuaternion& quaternion) {
    return glm::quat(
        quaternion.getW(),
        quaternion.getX(),
        quaternion.getY(),
        quaternion.getZ()
    );
}

btQuaternion Quaternion(const glm::quat& quaternion) {
    return btQuaternion(
        quaternion.x,
        quaternion.y,
        quaternion.z,
        quaternion.w
    );
}

std::ostream& operator<<(std::ostream& os, const btVector3& vector) {
    os << vector.x() << ", " << vector.y() << ", " << vector.z();
    return os;
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& vector) {
    os << vector.x << ", " << vector.y << ", " << vector.z;
    return os;
}

