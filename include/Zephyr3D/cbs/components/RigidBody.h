#ifndef RigidBody_h
#define RigidBody_h

#include "Component.h"
#include "Transform.h"
#include "../../physics/CollisionObject.h"
#include "../connections/PropertyIn.h"
#include "../connections/PropertyOut.h"
#include "../connections/MessageOut.h"

namespace zephyr::cbs {

class RigidBody : public Component, public physics::CollisionObject {
public:
    RigidBody(class Object& object, ID_t id, btScalar mass, btCollisionShape* shape, int group = 1, int mask = -1);

    void Initialize() override;
    void Destroy() override;

    void OnCollision(const btCollisionObject* collider) override;
    void PhysicsUpdate() override;

    PropertyOut<RigidBody*> This{ this, this };
    PropertyIn<Transform*> TransformIn{ this };
    MessageOut<const btCollisionObject*> CollisionOut{ this };

private:
    btRigidBody* CreateRigibBody(btScalar mass, btCollisionShape* shape) const;

    int m_Group;
    int m_Mask;
};

}

#endif
