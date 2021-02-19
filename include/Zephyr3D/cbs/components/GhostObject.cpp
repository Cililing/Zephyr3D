#include "GhostObject.h"
#include "../Object.h"
#include "../../Scene.h"
#include "../../core/Math.h"

zephyr::cbs::GhostObject::GhostObject(class Object& object, ID_t id, btCollisionShape* shape, int group, int mask)
    : Component(object, id)
    , CollisionObject(new btGhostObject)
    , m_Group(group)
    , m_Mask(mask) {
    m_BulletHandle->setCollisionShape(shape);
    m_BulletHandle->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void zephyr::cbs::GhostObject::Initialize() {
    assert(TransformIn.Connected());

    btTransform transform;
    transform.setIdentity();

    transform.setOrigin(Vector3(TransformIn.Value()->GlobalPosition()));
    transform.setRotation(Quaternion(TransformIn.Value()->GlobalRotation()));

    m_BulletHandle->setWorldTransform(transform);
    m_BulletHandle->getCollisionShape()->setLocalScaling(Vector3(TransformIn.Value()->LocalScale()));

    Object().Scene().Physics().AddCollisionObject(this, m_Group, m_Mask);
}

void zephyr::cbs::GhostObject::Destroy() {
    Object().Scene().Physics().RemoveCollisionObject(this);
}

void zephyr::cbs::GhostObject::PhysicsUpdate() {
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(Vector3(TransformIn.Value()->GlobalPosition()));
    trans.setRotation(Quaternion(TransformIn.Value()->GlobalRotation()));
    m_BulletHandle->setWorldTransform(trans);
    m_BulletHandle->getCollisionShape()->setLocalScaling(Vector3(TransformIn.Value()->LocalScale()));
}

void zephyr::cbs::GhostObject::OnCollision(const btCollisionObject* collider) {
    CollisionOut.Send(collider);
}
