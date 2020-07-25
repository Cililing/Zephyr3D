#ifndef IPhysicalObject_h
#define IPhysicalObject_h

#include "btBulletCollisionCommon.h"

namespace zephyr::physics {

class CollisionObject {
public:
    CollisionObject(btCollisionObject* collision_object);

    CollisionObject() = delete;
    CollisionObject(const CollisionObject&) = delete;
    CollisionObject& operator=(const CollisionObject&) = delete;
    CollisionObject(CollisionObject&&) = delete;
    CollisionObject& operator=(CollisionObject&&) = delete;
    virtual ~CollisionObject() = default;

    virtual void OnCollision(const btCollisionObject* collider) = 0;
    virtual void PhysicsUpdate() = 0;

    btCollisionObject* BulletHandle() const { return m_BulletHandle; }

protected:
    btCollisionObject* m_BulletHandle;
};

}

#endif
