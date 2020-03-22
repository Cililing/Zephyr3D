#include "RigidBody.h"

RigidBody::RigidBody(btScalar mass, btCollisionShape* shape, int group, int mask)
    : m_Group(group)
    , m_Mask(mask) {
    btVector3 local_inertia(0, 0, 0);

    if (mass != 0.0f) {
        shape->calculateLocalInertia(mass, local_inertia);
    }

    btTransform start;
    start.setIdentity();

    // Resources will be deleted by PhysicsManager
    btDefaultMotionState* motion_state = new btDefaultMotionState(start);
    btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, shape, local_inertia);

    m_RigidBody = new btRigidBody(info);
    m_RigidBody->setUserPointer((IPhysicalObject*)this);
}

void RigidBody::Initialize() {
    btTransform transform;
    transform.setIdentity();

    auto pos = TransformIn.Value()->Position();
    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    auto rot = TransformIn.Value()->Rotation();
    transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));

    btVector3 transform_scale = btVector3(TransformIn.Value()->Scale().x, TransformIn.Value()->Scale().y, TransformIn.Value()->Scale().z);

    m_RigidBody->setWorldTransform(transform);
    m_RigidBody->getMotionState()->setWorldTransform(transform);
    m_RigidBody->getCollisionShape()->setLocalScaling(transform_scale);

    Object().Scene().AddRigidBody(m_RigidBody, m_Group, m_Mask);
}

void RigidBody::Destroy() {
    Object().Scene().RemoveRigidBody(m_RigidBody);
}

void RigidBody::OnCollision(const btCollisionObject* collider) {
    CollisionOut.Send(collider);
}

void RigidBody::PhysicsUpdate() {
    btTransform trans;
    m_RigidBody->getMotionState()->getWorldTransform(trans);

    auto origin = trans.getOrigin();
    TransformIn.Value()->Position(glm::vec3(origin.getX(), origin.getY(), origin.getZ()));

    auto rot = trans.getRotation();
    TransformIn.Value()->Rotation(glm::quat(rot.getW(), rot.getX(), rot.getY(), rot.getZ()));

    auto scale = m_RigidBody->getCollisionShape()->getLocalScaling();
    TransformIn.Value()->Scale(glm::vec3(scale.getX(), scale.getY(), scale.getZ()));
}
