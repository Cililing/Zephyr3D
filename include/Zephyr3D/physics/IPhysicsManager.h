#ifndef IPhysicsManager_h
#define IPhysicsManager_h

#include "CollisionObject.h"

#pragma warning(push, 0)
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
#include "BulletDynamics/MLCPSolvers/btMLCPSolver.h"
#include "BulletDynamics/MLCPSolvers/btDantzigSolver.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#pragma warning(pop)

namespace zephyr::physics {

class IPhysicsManager {
public:
    IPhysicsManager() = default;
    IPhysicsManager(const IPhysicsManager&) = delete;
    IPhysicsManager& operator=(const IPhysicsManager&) = delete;
    IPhysicsManager(IPhysicsManager&&) = delete;
    IPhysicsManager& operator=(IPhysicsManager&&) = delete;
    virtual ~IPhysicsManager() = default;

    virtual void AddCollisionObject(CollisionObject* collision_object, int group = 1, int mask = -1) = 0;
    virtual void RemoveCollisionObject(CollisionObject* collision_object) = 0;
    virtual void AddRigidBody(CollisionObject* rigid_body, int group = 1, int mask = -1) = 0;
    virtual void RemoveRigidBody(CollisionObject* rigid_body) = 0;
    virtual void AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies = false) = 0;
    virtual void RemoveConstraint(btTypedConstraint* constraint) = 0;
    virtual void AddVehicle(btRaycastVehicle* vehicle) = 0;
    virtual void RemoveVehicle(btRaycastVehicle* vehicle) = 0;
    virtual void Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result) = 0;
    virtual void Gravity(btVector3 gravity) = 0;
    virtual btVector3 Gravity() const = 0;
    virtual btDynamicsWorld* DynamicsWorld() = 0;
};

}

#endif
