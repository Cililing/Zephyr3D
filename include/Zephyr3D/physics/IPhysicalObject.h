#ifndef IPhysicalObject_h
#define IPhysicalObject_h

#include "btBulletCollisionCommon.h"

namespace zephyr::physics {

class IPhysicalObject {
public:
    IPhysicalObject() = default;
    IPhysicalObject(const IPhysicalObject&) = delete;
    IPhysicalObject& operator=(const IPhysicalObject&) = delete;
    IPhysicalObject(IPhysicalObject&&) = delete;
    IPhysicalObject& operator=(IPhysicalObject&&) = delete;
    virtual ~IPhysicalObject() = default;

    virtual void OnCollision(const btCollisionObject* collider) = 0;
    virtual void PhysicsUpdate() = 0;
};

}

#endif
