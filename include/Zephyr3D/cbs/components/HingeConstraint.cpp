#include "HingeConstraint.h"

#include "RigidBody.h"

HingeConstraint::HingeConstraint(btTransform rb_a_frame, btTransform rb_b_frame, bool use_reference_frame_a)
    : m_Constraint(nullptr)
    , m_RbAFrame(rb_a_frame)
    , m_RbBFrame(rb_b_frame) 
    , m_UseReferenceFrameA(use_reference_frame_a) {
}

void HingeConstraint::Initialize() {
    m_Constraint = new btHingeConstraint(*RigidBodyA.Value()->Handle(), *RigidBodyB.Value()->Handle(), m_RbAFrame, m_RbBFrame, m_UseReferenceFrameA);
    Object().Scene().AddConstraint(m_Constraint);
}

void HingeConstraint::Destroy() {
    Object().Scene().RemoveConstraint(m_Constraint);
}
