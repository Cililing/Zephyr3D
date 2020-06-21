#include "PhysicsManager.h"

zephyr::physics::PhysicsManager::PhysicsManager(btIDebugDraw* debug_drawer) 
    : m_DebugDrawer(debug_drawer) {
}

void zephyr::physics::PhysicsManager::Initialize() {
    INFO_LOG(Logger::ESender::Physics, "Initializing physics manager");

    m_CollisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    m_Dispatcher = std::make_unique<btCollisionDispatcher>(m_CollisionConfiguration.get());
    m_Broadphase = std::make_unique<btDbvtBroadphase>();
    m_Solver = std::make_unique<btMLCPSolver>(new btDantzigSolver());

    m_World = std::make_unique<btDiscreteDynamicsWorld>(m_Dispatcher.get(), m_Broadphase.get(), m_Solver.get(), m_CollisionConfiguration.get());
    m_World->getSolverInfo().m_minimumSolverBatchSize = 1;
    m_World->getSolverInfo().m_globalCfm = 0.0001;
    m_World->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

    m_World->setGravity(btVector3(btScalar(0), btScalar(-10), btScalar(0)));

    m_World->setDebugDrawer(m_DebugDrawer.get());
    m_World->getDebugDrawer()->setDebugMode(1);
}

void zephyr::physics::PhysicsManager::StepSimulation(float delta_time) {
    m_World->stepSimulation(delta_time);
    m_World->debugDrawWorld();

    // Callbacks
    btDispatcher* dispatcher = m_World->getDispatcher();
    const int num_manifold = dispatcher->getNumManifolds();
    for (int i = 0; i < num_manifold; i++) {
        btPersistentManifold* contact = dispatcher->getManifoldByIndexInternal(i);
        const btCollisionObject* A = contact->getBody0();
        const btCollisionObject* B = contact->getBody1();

        const int num_contacts = contact->getNumContacts();
        for (int j = 0; j < num_contacts; j++) {
            btManifoldPoint& point = contact->getContactPoint(j);
            if (point.getDistance() < 0.0f) {
                static_cast<IPhysicalObject*>(A->getUserPointer())->OnCollision(B);
                static_cast<IPhysicalObject*>(B->getUserPointer())->OnCollision(A);
            }
        }
    }

    btCollisionObjectArray objects = m_World->getCollisionObjectArray();
    int num_objects = objects.size();
    for (int i = 0; i < num_objects; i++) {
        static_cast<IPhysicalObject*>(objects[i]->getUserPointer())->PhysicsUpdate();
    }
}

void zephyr::physics::PhysicsManager::ExitPhysics() {
    INFO_LOG(Logger::ESender::Physics, "Exiting physics");

    if (m_World) {
        int i = m_World->getNumConstraints() - 1;
        for (; i >= 0; i--) {
            m_World->removeConstraint(m_World->getConstraint(i));
        }

        i = m_World->getNumCollisionObjects() - 1;
        for (; i >= 0; i--) {
            btCollisionObject* obj = m_World->getCollisionObjectArray()[i];

            if (btRigidBody* body = btRigidBody::upcast(obj)) {
                if (auto shape = body->getCollisionShape()) {
                    delete shape;
                }

                if (auto motion_state = body->getMotionState()) {
                    delete motion_state;
                }
            }

            m_World->removeCollisionObject(obj);
            delete obj;
        }
    }
}

void zephyr::physics::PhysicsManager::AddCollisionObject(btCollisionObject* collision_object, int collision_filter_group, int collision_filter_mask) {
    m_World->addCollisionObject(collision_object, collision_filter_group, collision_filter_mask);
}

void zephyr::physics::PhysicsManager::RemoveCollisionObject(btCollisionObject* collision_object) {
    m_World->removeCollisionObject(collision_object);
}

void zephyr::physics::PhysicsManager::AddRigidBody(btRigidBody* rigid_body, int group, int mask) {
    m_World->addRigidBody(rigid_body, group, mask);
}

void zephyr::physics::PhysicsManager::RemoveRigidBody(btRigidBody* rigid_body) {
    m_World->removeRigidBody(rigid_body);
}

void zephyr::physics::PhysicsManager::AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies) {
    m_World->addConstraint(constraint, disable_collisions_between_linked_bodies);
}

void zephyr::physics::PhysicsManager::RemoveConstraint(btTypedConstraint* constraint) {
    m_World->removeConstraint(constraint);
}

void zephyr::physics::PhysicsManager::AddVehicle(btRaycastVehicle* vehicle) {
    m_World->addVehicle(vehicle);
}

void zephyr::physics::PhysicsManager::RemoveVehicle(btRaycastVehicle* vehicle) {
    m_World->removeVehicle(vehicle);
}

void zephyr::physics::PhysicsManager::Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result) {
    m_World->rayTest(from, to, result);
}

void zephyr::physics::PhysicsManager::Gravity(btVector3 gravity) {
    m_World->setGravity(gravity);
}

btVector3 zephyr::physics::PhysicsManager::Gravity() const {
    return m_World->getGravity();
}

btDynamicsWorld* zephyr::physics::PhysicsManager::DynamicsWorld() {
    return m_World.get();
}
