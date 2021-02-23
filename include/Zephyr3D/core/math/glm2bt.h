#ifndef glm2bt_h
#define glm2bt_h

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <bullet/btBulletCollisionCommon.h>
#pragma warning(pop)

#include <iostream>

namespace zephyr {

glm::vec3 Vector3(const btVector3& vector);
btVector3 Vector3(const glm::vec3& vector);

glm::quat Quaternion(const btQuaternion& quaternion);
btQuaternion Quaternion(const glm::quat& quaternion);

std::ostream& operator<<(std::ostream& os, const btVector3& vector);
std::ostream& operator<<(std::ostream& os, const glm::vec3& vector);

}

#endif
