#ifndef GhostObject_h
#define GhostObject_h

#include "Component.h"
#include "../../physics/IPhysicalObject.h"
#include "../connections/PropertyIn.h"
#include "../connections/MessageOut.h"
#include "../Object.h"
#include "../../scenes/Scene.h"

#pragma warning(push, 0)
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#pragma warning(pop)


class GhostObject : public Component, public IPhysicalObject {
public:
    GhostObject(btCollisionShape* shape, int group = 1, int mask = -1);

    void Initialize() override;
    void Destroy() override;

    void PhysicsUpdate() override;
    void OnCollision(const btCollisionObject* collider) override;

    PropertyIn<Transform*> TransformIn{ this };
    MessageOut<const btCollisionObject*> CollisionOut{ this };

private:
    btGhostObject* m_GhostObject;
    int m_Group;
    int m_Mask;
};

#endif
