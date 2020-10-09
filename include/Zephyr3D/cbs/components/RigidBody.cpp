#include "RigidBody.h"

RigidBody::RigidBody(class Object& object, ID_t id, btScalar mass, btCollisionShape* shape, int group, int mask)
    : Component(object, id)
    , CollisionObject(CreateRigibBody(mass, shape))
    , m_Group(group)
    , m_Mask(mask) {

}

void RigidBody::Initialize() {
    btTransform transform;
    transform.setIdentity();

    transform.setOrigin(Vector3(TransformIn.Value()->Position()));
    transform.setRotation(Quaternion(TransformIn.Value()->Rotation()));

    m_BulletHandle->setWorldTransform(transform);
    static_cast<btRigidBody*>(m_BulletHandle)->getMotionState()->setWorldTransform(transform);
    m_BulletHandle->getCollisionShape()->setLocalScaling(Vector3(TransformIn.Value()->Scale()));

    Object().Scene().AddRigidBody(this, m_Group, m_Mask);
}

void RigidBody::Destroy() {
    Object().Scene().RemoveRigidBody(this);
}

void RigidBody::OnCollision(const btCollisionObject* collider) {
    CollisionOut.Send(collider);
}

void RigidBody::PhysicsUpdate() {
    btTransform trans;
    btRigidBody* rigid_body = static_cast<btRigidBody*>(m_BulletHandle);

    rigid_body->getMotionState()->getWorldTransform(trans);

    TransformIn.Value()->Position(Vector3(trans.getOrigin()));
    TransformIn.Value()->Rotation(Quaternion(trans.getRotation()));
    TransformIn.Value()->Scale(Vector3(rigid_body->getCollisionShape()->getLocalScaling()));
}

btRigidBody* RigidBody::CreateRigibBody(btScalar mass, btCollisionShape* shape) const {
    btVector3 local_inertia(0, 0, 0);

    if (mass != 0.0f) {
        shape->calculateLocalInertia(mass, local_inertia);
    }

    btTransform start;
    start.setIdentity();

    btDefaultMotionState* motion_state = new btDefaultMotionState(start);
    btRigidBody::btRigidBodyConstructionInfo info(mass, motion_state, shape, local_inertia);

    return new btRigidBody(info);
}
