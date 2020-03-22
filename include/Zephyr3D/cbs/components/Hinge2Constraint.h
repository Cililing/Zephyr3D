#ifndef Hinge2Joint_h
#define Hinge2Joint_h

#include "Component.h"
#include "../connections/PropertyIn.h"
#include "../../physics/PhysicsManager.h"

class RigidBody;
class Hinge2Constraint : public Component {
public:
    Hinge2Constraint(const btVector3& parent_axis, const btVector3& child_axis, const btVector3& anchor);

    void Initialize() override;
    void Destroy() override;

    btHinge2Constraint* Handle() { return m_Constraint; }

    PropertyIn<RigidBody*> RigidBodyA{ this };
    PropertyIn<RigidBody*> RigidBodyB{ this };

private:
    btHinge2Constraint* m_Constraint;

    btVector3 m_ParentAxis;
    btVector3 m_ChildAxis;
    btVector3 m_Anchor;
};

#endif
