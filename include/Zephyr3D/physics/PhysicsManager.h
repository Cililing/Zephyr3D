#ifndef PhysicsManager_h
#define PhysicsManager_h

#include "IPhysicalObject.h"
#include "PhysicsRenderer.h"
#include "../debuging/Logger.h"

#pragma warning(push, 0)
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/NarrowPhaseCollision/btRaycastCallback.h"
#include "BulletDynamics/MLCPSolvers/btMLCPSolver.h"
#include "BulletDynamics/MLCPSolvers/btDantzigSolver.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

#include <assert.h>
#include <vector>
#pragma warning(pop)

namespace zephyr::physics {

class PhysicsManager {
public:
    explicit PhysicsManager(zephyr::rendering::DrawManager& draw_manager);

    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;
    PhysicsManager(PhysicsManager&&) = delete;
    PhysicsManager& operator=(PhysicsManager&&) = delete;
    ~PhysicsManager() = default;

    void Initialize();
    void StepSimulation(float delta_time);
    void ExitPhysics();

    void AddCollisionObject(btCollisionObject* collision_object, int collision_filter_group = 1, int collision_filter_mask = -1);
    void RemoveCollisionObject(btCollisionObject* collision_object);

    void AddRigidBody(btRigidBody* rigid_body, int group = 1, int mask = -1);
    void RemoveRigidBody(btRigidBody* rigid_body);

    void AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies = false);
    void RemoveConstraint(btTypedConstraint* constraint);

    void AddVehicle(btRaycastVehicle* vehicle);
    void RemoveVehicle(btRaycastVehicle* vehicle);

    void Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result);

    void Gravity(btVector3 gravity);
    btVector3 Gravity() const;

    btDynamicsWorld* DynamicsWorld();

private:
    std::unique_ptr<btCollisionConfiguration> m_CollisionConfiguration;
    std::unique_ptr<btCollisionDispatcher> m_Dispatcher;
    std::unique_ptr<btBroadphaseInterface> m_Broadphase;
    std::unique_ptr<btConstraintSolver> m_Solver;
    std::unique_ptr<btDynamicsWorld> m_World;
    
    PhysicsRenderer m_PhysicsRenderer;
};

}

#endif
