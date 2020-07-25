#include "GhostObject.h"

GhostObject::GhostObject(btCollisionShape* shape, int group, int mask)
    : CollisionObject(new btGhostObject)
    , m_Group(group)
    , m_Mask(mask) {
    m_BulletHandle->setCollisionShape(shape);
    m_BulletHandle->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void GhostObject::Initialize() {
    btTransform transform;
    transform.setIdentity();

    transform.setOrigin(Vector3(TransformIn.Value()->Position()));
    transform.setRotation(Quaternion(TransformIn.Value()->Rotation()));

    m_BulletHandle->setWorldTransform(transform);
    m_BulletHandle->getCollisionShape()->setLocalScaling(Vector3(TransformIn.Value()->Scale()));

    Object().Scene().AddCollisionObject(this, m_Group, m_Mask);
}

void GhostObject::Destroy() {
    Object().Scene().RemoveCollisionObject(this);
}

void GhostObject::PhysicsUpdate() {
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(Vector3(TransformIn.Value()->Position()));
    trans.setRotation(Quaternion(TransformIn.Value()->Rotation()));
    m_BulletHandle->setWorldTransform(trans);
    m_BulletHandle->getCollisionShape()->setLocalScaling(Vector3(TransformIn.Value()->Scale()));
}

void GhostObject::OnCollision(const btCollisionObject* collider) {
    CollisionOut.Send(collider);
}
