#include "CollisionObject.h"

zephyr::physics::CollisionObject::CollisionObject(btCollisionObject* collision_object)
    : m_BulletHandle(collision_object) {

    m_BulletHandle->setUserPointer(this);
}
