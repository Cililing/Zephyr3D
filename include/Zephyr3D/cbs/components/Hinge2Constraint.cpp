#include "Hinge2Constraint.h"
#include "RigidBody.h"

Hinge2Constraint::Hinge2Constraint(const btVector3& parent_axis, const btVector3& child_axis, const btVector3& anchor)
    : m_Constraint(nullptr)
    , m_ParentAxis(parent_axis)
    , m_ChildAxis(child_axis)
    , m_Anchor(anchor) {
}

void Hinge2Constraint::Initialize() {
    m_Constraint = new btHinge2Constraint(*RigidBodyA.Value()->Handle(), *RigidBodyB.Value()->Handle(), m_Anchor, m_ParentAxis, m_ChildAxis);
    Object().Scene().AddConstraint(m_Constraint, true);
}

void Hinge2Constraint::Destroy() {
    Object().Scene().RemoveConstraint(m_Constraint);
}
