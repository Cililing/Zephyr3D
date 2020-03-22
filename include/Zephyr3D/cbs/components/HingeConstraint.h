#ifndef HingeConstraint_h
#define HingeConstarint_h

#include "Component.h"
#include "../connections/PropertyIn.h"
#include "../../physics/PhysicsManager.h"

class RigidBody;
class HingeConstraint : public Component {
public:
    HingeConstraint(btTransform rb_a_frame, btTransform rb_b_frame, bool use_reference_frame_a = false);

    void Initialize() override;
    void Destroy() override;

    btHingeConstraint* Handle() { return m_Constraint; }

    PropertyIn<RigidBody*> RigidBodyA{ this };
    PropertyIn<RigidBody*> RigidBodyB{ this };
private:
    btHingeConstraint* m_Constraint;

    btTransform m_RbAFrame;
    btTransform m_RbBFrame;
    bool m_UseReferenceFrameA;
};

#endif
