#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(btIDebugDraw* debug_drawer) 
    : m_DebugDrawer(debug_drawer) {
}

PhysicsManager::~PhysicsManager() {
    //TODO maybe unique ptr
    delete m_DebugDrawer;
}

void PhysicsManager::Initialize() {
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

    if (m_DebugDrawer) {
        m_World->setDebugDrawer(m_DebugDrawer);
    }
}

void PhysicsManager::StepSimulation(float delta_time) {
    m_World->stepSimulation(delta_time);
    //m_World->debugDrawWorld();

    // Callbacks
    btDispatcher* dispatcher = m_World->getDispatcher();
    int num_manifold = dispatcher->getNumManifolds();
    for (int i = 0; i < num_manifold; i++) {
        btPersistentManifold* contact = dispatcher->getManifoldByIndexInternal(i);
        const btCollisionObject* A = contact->getBody0();
        const btCollisionObject* B = contact->getBody1();

        int num_contacts = contact->getNumContacts();
        for (int j = 0; j < num_contacts; j++) {
            btManifoldPoint& point = contact->getContactPoint(j);
            if (point.getDistance() < 0.0f) {
                ((IPhysicalObject*)A->getUserPointer())->OnCollision(B);
                ((IPhysicalObject*)B->getUserPointer())->OnCollision(A);
            }
        }
    }

    btCollisionObjectArray objects = m_World->getCollisionObjectArray();
    int num_objects = objects.size();
    for (int i = 0; i < num_objects; i++) {
        ((IPhysicalObject*)objects[i]->getUserPointer())->PhysicsUpdate();
    }
}

void PhysicsManager::ExitPhysics() {
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

void PhysicsManager::AddCollisionObject(btCollisionObject* collision_object, int collision_filter_group, int collision_filter_mask) {
    m_World->addCollisionObject(collision_object, collision_filter_group, collision_filter_mask);
}

void PhysicsManager::RemoveCollisionObject(btCollisionObject* collision_object) {
    m_World->removeCollisionObject(collision_object);
}

void PhysicsManager::AddRigidBody(btRigidBody* rigid_body) {
    m_World->addRigidBody(rigid_body);
}

void PhysicsManager::AddRigidBody(btRigidBody* rigid_body, int group, int mask) {
    m_World->addRigidBody(rigid_body, group, mask);
}

void PhysicsManager::RemoveRigidBody(btRigidBody* rigid_body) {
    m_World->removeRigidBody(rigid_body);
}

void PhysicsManager::AddConstraint(btTypedConstraint* constraint, bool disable_collisions_between_linked_bodies) {
    m_World->addConstraint(constraint, disable_collisions_between_linked_bodies);
}

void PhysicsManager::RemoveConstraint(btTypedConstraint* constraint) {
    m_World->removeConstraint(constraint);
}

void PhysicsManager::AddVehicle(btRaycastVehicle* vehicle) {
    m_World->addVehicle(vehicle);
}

void PhysicsManager::RemoveVehicle(btRaycastVehicle* vehicle) {
    m_World->removeVehicle(vehicle);
}

void PhysicsManager::Raycast(const btVector3& from, const btVector3& to, btCollisionWorld::RayResultCallback& result) {
    m_World->rayTest(from, to, result);
}
