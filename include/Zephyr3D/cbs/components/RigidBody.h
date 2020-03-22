#ifndef RigidBody_h
#define RigidBody_h

#include "Component.h"
#include "../../scenes/Scene.h"
#include "../../physics/PhysicsManager.h"
#include "../../physics/IPhysicalObject.h"
#include "../connections/PropertyIn.h"
#include "../connections/PropertyOut.h"
#include "../connections/MessageOut.h"


class RigidBody : public Component, public IPhysicalObject {
public:
    RigidBody(btScalar mass, btCollisionShape* shape, int group = 1, int mask = -1);

    void Initialize() override;
    void Destroy() override;

    void OnCollision(const btCollisionObject* collider) override;
    void PhysicsUpdate() override;

    btRigidBody* Handle() { return m_RigidBody; }

    PropertyOut<RigidBody*> This{ this, this };
    PropertyIn<Transform*> TransformIn{ this };
    MessageOut<const btCollisionObject*> CollisionOut{ this };

private:
    btRigidBody* m_RigidBody;
    int m_Group;
    int m_Mask;
};

#endif
