#ifndef PhysicsManager_h
#define PhysicsManager_h

#include "IPhysicsManager.h"
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

class PhysicsManager : public IPhysicsManager {
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

    void AddCollisionObject(CollisionObject* collision_object, int group = 1, int mask = -1) override;
    void RemoveCollisionObject(CollisionObject* collision_object) override;

    void AddRigidBody(CollisionObject* rigid_body, int group = 1, int mask = -1) override;
    void RemoveRigidBody(CollisionObject* rigid_body) override;

    void AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies = false) override;
    void RemoveConstraint(btTypedConstraint* constraint) override;

    void AddVehicle(btRaycastVehicle* vehicle) override;
    void RemoveVehicle(btRaycastVehicle* vehicle) override;

    void Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result) override;

    void Gravity(btVector3 gravity) override;
    btVector3 Gravity() const override;

    btDynamicsWorld* DynamicsWorld() override;

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
