#ifndef GravityGun_h
#define GravityGun_h

#include <Zephyr3D/cbs/components/Component.h>
#include <Zephyr3D/cbs/components/Transform.h>
#include <Zephyr3D/cbs/connections/PropertyIn.h>

#include <Zephyr3D/cbs/Object.h>
#include <Zephyr3D/scenes/Scene.h>

#include <Zephyr3D/Engine.h>

#pragma warning(push, 0)
#include <GLFW/glfw3.h>
#pragma warning(pop)

class GravityGun : public Component {
public:
	GravityGun(float range, float impuls_force);

	void Initialize() override;
	void Update() override;

	PropertyIn<Transform*> TransformIn{ this };

private:
	int m_PickUpKey{ GLFW_MOUSE_BUTTON_1 };
	int m_PushKey{ GLFW_MOUSE_BUTTON_2 };

	float m_Range;
	float m_ImpulsForce;

	btRigidBody* m_Target{ nullptr };
	btPoint2PointConstraint* m_Constraint{ nullptr };
	btScalar m_OldPickingDistance;
	int m_SavedState;
	
};

#endif
