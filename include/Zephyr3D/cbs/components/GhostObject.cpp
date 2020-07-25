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

    auto pos = TransformIn.Value()->Position();
    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    auto rot = TransformIn.Value()->Rotation();
    transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));

    auto scale = TransformIn.Value()->Scale();

    m_BulletHandle->setWorldTransform(transform);
    m_BulletHandle->getCollisionShape()->setLocalScaling(btVector3(scale.x, scale.y, scale.z));

    Object().Scene().AddCollisionObject(this, m_Group, m_Mask);
}

void GhostObject::Destroy() {
    Object().Scene().RemoveCollisionObject(this);
}

void GhostObject::PhysicsUpdate() {
    glm::vec3 glm_pos = TransformIn.Value()->Position();
    auto origin = btVector3(glm_pos.x, glm_pos.y, glm_pos.z);

    glm::quat glm_rot = TransformIn.Value()->Rotation();
    auto rot = btQuaternion(glm_rot.x, glm_rot.y, glm_rot.z, glm_rot.w);

    glm::vec3 glm_scale = TransformIn.Value()->Scale();
    auto scale = btVector3(glm_scale.x, glm_scale.y, glm_scale.z);

    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(origin);
    trans.setRotation(rot);
    m_BulletHandle->setWorldTransform(trans);
    m_BulletHandle->getCollisionShape()->setLocalScaling(scale);
}

void GhostObject::OnCollision(const btCollisionObject* collider) {
    CollisionOut.Send(collider);
}
