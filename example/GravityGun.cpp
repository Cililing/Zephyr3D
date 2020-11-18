#include "GravityGun.h"

GravityGun::GravityGun(class zephyr::cbs::Object& object, ID_t id, float range, float impulse_force)
	: Component(object, id)
	, m_Range(range)
	, m_ImpulsForce(impulse_force * range) {

}

void GravityGun::Initialize() {
	RegisterUpdateCall();
}

void GravityGun::Update() {
	auto _from = TransformIn.Value()->Position();
	btVector3 from(_from.x, _from.y, _from.z);

	auto _direction = TransformIn.Value()->Front();
	btVector3 direction(_direction.x, _direction.y, _direction.z);

	btVector3 to = from + direction * m_Range;

	if (zephyr::Engine::Instance().GetInput().KeyPressed(m_PickUpKey)) {
		// Pick up rigidbody

		btCollisionWorld::ClosestRayResultCallback result(from, to);
		Object().Scene().Raycast(from, to, result);

		if (!result.hasHit()) {
			return;
		}

		m_Target = (btRigidBody*)btRigidBody::upcast(result.m_collisionObject);

		if (m_Target->isStaticObject()) {
			m_Target = nullptr;
			return;
		}

		m_SavedState = m_Target->getActivationState();
		btVector3 pick_position = result.m_hitPointWorld;
		btVector3 local_pivot = m_Target->getCenterOfMassTransform().inverse() * pick_position;
		m_Constraint = new btPoint2PointConstraint(*m_Target, local_pivot);
		Object().Scene().AddConstraint(m_Constraint, true);
		m_Constraint->m_setting.m_impulseClamp = 30.0f;
		m_Constraint->m_setting.m_tau = 0.001f;
		m_OldPickingDistance = (pick_position - from).length();

	} else if (m_Target != nullptr && zephyr::Engine::Instance().GetInput().KeyHold(m_PickUpKey)) {
		// Move picked body
		
		m_Target->activate();
		btVector3 direction = (to - from).normalize() * m_OldPickingDistance;
		btVector3 new_pivot = from + direction;
		m_Constraint->setPivotB(new_pivot);

	} else if (m_Target != nullptr && zephyr::Engine::Instance().GetInput().KeyReleased(m_PickUpKey)) {
		// Let go

		m_Target->forceActivationState(m_SavedState);
		m_Target->activate();
		Object().Scene().RemoveConstraint(m_Constraint);
		delete m_Constraint;
		m_Constraint = nullptr;
		m_Target = nullptr;
	} else if (zephyr::Engine::Instance().GetInput().KeyPressed(m_PushKey)) {
		// Push

		btCollisionWorld::ClosestRayResultCallback result(from, to);
		Object().Scene().Raycast(from, to, result);

		if (!result.hasHit()) {
			return;
		}

		m_Target = (btRigidBody*)btRigidBody::upcast(result.m_collisionObject);

		if (m_Target->isStaticObject()) {
			m_Target = nullptr;
			return;
		}

		m_Target->applyCentralImpulse(direction * m_ImpulsForce);
		m_Target->activate();
	}
}
