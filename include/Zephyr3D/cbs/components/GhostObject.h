#ifndef GhostObject_h
#define GhostObject_h

#include "Component.h"
#include "Transform.h"
#include "../../physics/CollisionObject.h"
#include "../connections/PropertyIn.h"
#include "../connections/MessageOut.h"

#pragma warning(push, 0)
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#pragma warning(pop)

namespace zephyr::cbs {

class GhostObject : public Component, public physics::CollisionObject {
public:
    GhostObject(class Object& object, ID_t id, btCollisionShape* shape, int group, int mask);

    void Initialize() override;
    void Destroy() override;

    void PhysicsUpdate() override;
    void OnCollision(const btCollisionObject* collider) override;

    PropertyIn<Transform*> TransformIn{ this };
    MessageOut<const btCollisionObject*> CollisionOut{ this };

private:
    int m_Group;
    int m_Mask;
};

}

#endif
