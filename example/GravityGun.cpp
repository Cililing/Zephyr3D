#include "GravityGun.h"

GravityGun::GravityGun(float range)
	: m_Range(range) {

}

void GravityGun::Initialize() {
	RegisterUpdateCall();
}

void GravityGun::Update() {
	auto _from = TransformIn.Value()->Position();
	btVector3 from(_from.x, _from.y, _from.z);

	auto _to = _from + TransformIn.Value()->Front() * m_Range;
	btVector3 to(_to.x, _to.y, _to.z);

	btCollisionWorld::ClosestRayResultCallback result(from, to);
	Object().Scene().Raycast(from, to, result);

	if (result.hasHit() && zephyr::Engine::Instance().GetInput().KeyPressed(m_PushKey)) {
		((btRigidBody*)result.m_collisionObject)->applyCentralImpulse(to);
		((btRigidBody*)result.m_collisionObject)->activate();
	}
}
