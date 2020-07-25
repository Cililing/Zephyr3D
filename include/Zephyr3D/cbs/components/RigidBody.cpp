#include "RigidBody.h"

RigidBody::RigidBody(btScalar mass, btCollisionShape* shape, int group, int mask)
    : CollisionObject(CreateRigibBody(mass, shape))
    , m_Group(group)
    , m_Mask(mask) {

}

void RigidBody::Initialize() {
    btTransform transform;
    transform.setIdentity();

    auto pos = TransformIn.Value()->Position();
    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    auto rot = TransformIn.Value()->Rotation();
    transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));

    btVector3 transform_scale = btVector3(TransformIn.Value()->Scale().x, TransformIn.Value()->Scale().y, TransformIn.Value()->Scale().z);

    m_BulletHandle->setWorldTransform(transform);
    static_cast<btRigidBody*>(m_BulletHandle)->getMotionState()->setWorldTransform(transform);
    m_BulletHandle->getCollisionShape()->setLocalScaling(transform_scale);

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

    auto origin = trans.getOrigin();
    TransformIn.Value()->Position(glm::vec3(origin.getX(), origin.getY(), origin.getZ()));

    auto rot = trans.getRotation();
    TransformIn.Value()->Rotation(glm::quat(rot.getW(), rot.getX(), rot.getY(), rot.getZ()));

    auto scale = rigid_body->getCollisionShape()->getLocalScaling();
    TransformIn.Value()->Scale(glm::vec3(scale.getX(), scale.getY(), scale.getZ()));
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
