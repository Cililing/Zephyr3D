#ifndef Controller_h
#define Controller_h

#include "Component.h"
#include "../connections/PropertyIn.h"
#include "../connections/MessageOut.h"
#include "../connections/MessageIn.h"

#include "../../utilities/Input.h"
#include "../../utilities/Time.h"

#include "btBulletCollisionCommon.h"
#include "../../physics/IPhysicalObject.h"

class Vehicle;
class Controller : public Component {
public:
    Controller(float engine_force, float breaking_force, float steering, float max_steering);

    void Initialize() override;
    void Update() override;

    PropertyIn<Vehicle*> ControlledVehicle{ this };

private:
    float m_MaxEngineForce;
    float m_MaxBreakingForce;
    float m_Steering;
    float m_MaxSteering;

    float m_CurrEngineForce{ 0.0f };
    float m_CurrBreakingForce{ 0.0f };
    float m_CurrSteering{ 0.0f };

    GLenum m_Forward{ GLFW_KEY_W };
    GLenum m_Backward{ GLFW_KEY_S };
    GLenum m_Left{ GLFW_KEY_A } ;
    GLenum m_Right{ GLFW_KEY_D };
};

#endif
