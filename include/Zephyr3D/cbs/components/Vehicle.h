#ifndef Vehicle_h
#define Vehicle_h

#include "Component.h"
#include "../connections/PropertyIn.h"
#include "../connections/PropertyOut.h"
#include "../connections/MessageIn.h"
#include "../../utilities/Time.h"

#pragma warning(push, 0)
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"
#include <glm/gtx/rotate_vector.hpp>
#pragma warning(pop)

#define _USE_MATH_DEFINES
#include <math.h>

// FIX: Chassis front is transform right
class RigidBody;
class Transform;
class Vehicle : public Component {
public:
    Vehicle(float suspension_rest_length, float steering_clamp, float wheel_radius, float wheel_width);

    void Initialize() override;
    void Update() override;
    void Destroy() override;

    void ApplyEngineForce(float force);
    void Brake(float brake);
    void Steer(float steering);

    btRaycastVehicle* PhysicsHandle() { return m_Vehicle; }

    PropertyOut<Vehicle*> This{ this, this };
    PropertyIn<RigidBody*> Chassis{ this };
    PropertyIn<Transform*> FrontLeftWheel{ this };
    PropertyIn<Transform*> FrontRightWheel{ this };
    PropertyIn<Transform*> MiddleLeftWheel{ this };
    PropertyIn<Transform*> MiddleRightWheel{ this };
    PropertyIn<Transform*> BackLeftWheel{ this };
    PropertyIn<Transform*> BackRightWheel{ this };

private:
    btRaycastVehicle* m_Vehicle;
    btVehicleRaycaster* m_VehicleRaycaster;

    float m_SteeringClamp;
    btScalar m_SuspensionRestLength;

    float m_MaxEngineForce{ 0.0f };
    float m_MaxBreakingForce{ 0.0f };
    float m_VehicleSteering{ 0.0f }; 
    btVector3 m_WheelDirectionCS0{ 0, -1, 0 };
    btVector3 m_WheelAxleCS{ 1, 0, 0 };

    float m_WheelRadius;
    float m_WheelWidth;
    float m_WheelCircumference;
    float m_PrevSteer{ 0.0f };
};

#endif
