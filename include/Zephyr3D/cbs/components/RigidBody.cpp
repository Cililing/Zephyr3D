#include "RigidBody.h"
#include "../../Scene.h"
#include "../../physics/PhysicsManager.h"
#include "../../core/Math.h"

zephyr::cbs::RigidBody::RigidBody(class Object& object, ID_t id, btScalar mass, btCollisionShape* shape, int group, int mask)
    : Component(object, id)
    , CollisionObject(CreateRigibBody(mass, shape))
    , m_Group(group)
    , m_Mask(mask) {

}

void zephyr::cbs::RigidBody::Initialize() {
    assert(TransformIn.Connected());

    btTransform transform;
    transform.setIdentity();

    transform.setOrigin(Vector3(TransformIn.Value()->GlobalPosition()));
    transform.setRotation(Quaternion(TransformIn.Value()->LocalRotation()));
    

    m_BulletHandle->setWorldTransform(transform);
    static_cast<btRigidBody*>(m_BulletHandle)->getMotionState()->setWorldTransform(transform);
    m_BulletHandle->getCollisionShape()->setLocalScaling(Vector3(TransformIn.Value()->LocalScale()));

    Object().Scene().Physics().AddRigidBody(this, m_Group, m_Mask);
}

void zephyr::cbs::RigidBody::Destroy() {
    Object().Scene().Physics().RemoveRigidBody(this);
}

void zephyr::cbs::RigidBody::OnCollision(const btCollisionObject* collider) {
    CollisionOut.Send(collider);
}

void zephyr::cbs::RigidBody::PhysicsUpdate() {
    btTransform trans;
    auto* rigid_body = static_cast<btRigidBody*>(m_BulletHandle);
    rigid_body->getMotionState()->getWorldTransform(trans);

    auto matrix = new float[16];
    trans.getOpenGLMatrix(matrix);

    auto glm_trans = glm::make_mat4(matrix);
    glm_trans = glm::scale(glm_trans, Vector3(m_BulletHandle->getCollisionShape()->getLocalScaling()));
    TransformIn.Value()->GlobalModel(glm_trans);
}

btRigidBody* zephyr::cbs::RigidBody::CreateRigibBody(btScalar mass, btCollisionShape* shape) const {
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
