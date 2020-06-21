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
	GravityGun(float range);

	void Initialize() override;
	void Update() override;

	PropertyIn<Transform*> TransformIn{ this };

private:
	float m_Range;

	int m_PickUpKey{ GLFW_MOUSE_BUTTON_1 };
	int m_PushKey{ GLFW_MOUSE_BUTTON_2 };
};

#endif
