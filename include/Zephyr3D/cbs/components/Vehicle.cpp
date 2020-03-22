#include "Vehicle.h"

#include "../Object.h"
#include "../../scenes/Scene.h"
#include "RigidBody.h"
#include "Transform.h"


Vehicle::Vehicle(float suspension_rest_length, float steering_clamp, float wheel_radius, float wheel_width)
    : m_VehicleRaycaster(nullptr)
    , m_Vehicle(nullptr)
    , m_SuspensionRestLength(suspension_rest_length)
    , m_SteeringClamp(steering_clamp)
    , m_WheelRadius(wheel_radius)
    , m_WheelWidth(wheel_width) {
    if (m_WheelRadius < 0.0f) {
        WARNING_LOG(Logger::ESender::CBS, "Value of m_WheelRadius shoud not be negative, changing to 1.0f");
        m_WheelRadius = 1.0f;
    }
    
    if (m_WheelWidth < 0.0f) {
        WARNING_LOG(Logger::ESender::CBS, "Value of m_WheelWidth shoud not be negative, changing to 1.0f");
        m_WheelWidth = 1.0f;
    }

    m_WheelCircumference = 2 * M_PI * wheel_radius;
}

void Vehicle::Initialize() {
    assert(Chassis.Connected() && FrontLeftWheel.Connected() && FrontRightWheel.Connected() && BackLeftWheel.Connected() && BackRightWheel.Connected());

    btRaycastVehicle::btVehicleTuning tunning;

    m_VehicleRaycaster = new btDefaultVehicleRaycaster(Object().Scene().DynamicsWorld());
    m_Vehicle = new btRaycastVehicle(tunning, Chassis.Value()->Handle(), m_VehicleRaycaster);

    Chassis.Value()->Handle()->setActivationState(DISABLE_DEACTIVATION);
    Object().Scene().AddVehicle(m_Vehicle);
    m_Vehicle->setCoordinateSystem(2, 1, 0);

    glm::vec3 chassis_pos = Chassis.Value()->TransformIn.Value()->Position();

    glm::vec3 diff = FrontLeftWheel.Value()->Position() - chassis_pos;
    m_Vehicle->addWheel(btVector3(diff.x, diff.y, diff.z), m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, tunning, true);

    diff = FrontRightWheel.Value()->Position() - chassis_pos;
    m_Vehicle->addWheel(btVector3(diff.x, diff.y, diff.z), m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, tunning, true);

    diff = BackLeftWheel.Value()->Position() - chassis_pos;
    m_Vehicle->addWheel(btVector3(diff.x, diff.y, diff.z), m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, tunning, false);

    diff = BackRightWheel.Value()->Position() - chassis_pos;
    m_Vehicle->addWheel(btVector3(diff.x, diff.y, diff.z), m_WheelDirectionCS0, m_WheelAxleCS, m_SuspensionRestLength, m_WheelRadius, tunning, false);

    for (int i = 0; i < m_Vehicle->getNumWheels(); i++) {
        btWheelInfo& wheel = m_Vehicle->getWheelInfo(i);

        // Hardcoded for now
        wheel.m_suspensionStiffness = 150.0f;
        wheel.m_wheelsDampingCompression = 0.3f;
        wheel.m_wheelsDampingRelaxation = 0.5f;
        wheel.m_frictionSlip = 200.0f;
        wheel.m_rollInfluence = 0.1f;
    }

    auto handle = Chassis.Value()->Handle();
    handle->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
    handle->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
    m_Vehicle->resetSuspension();
    for (int i = 0; i < m_Vehicle->getNumWheels(); i++) {
        m_Vehicle->updateWheelTransform(i, true);
    }

    RegisterUpdateCall();
}

void Vehicle::Update() {
    const float speed = std::abs(m_Vehicle->getCurrentSpeedKmHour()) / 3.6f; // km/h to m/s
    const float rotation = speed * g_Time.FixedDeltaTime() / m_WheelCircumference * 2 * M_PI;

    // Not the best solution but works for now
    const float delta_steer = m_Vehicle->getWheelInfo(0).m_steering - m_PrevSteer;

    FrontLeftWheel.Value()->Rotate(glm::vec3(0.0f, delta_steer, 0.0f));
    FrontLeftWheel.Value()->RotateRelative(glm::vec3(rotation, 0.0f, 0.0f));
    FrontRightWheel.Value()->Rotate(glm::vec3(0.0f, delta_steer, 0.0f));
    FrontRightWheel.Value()->RotateRelative(glm::vec3(-rotation, 0.0f, 0.0f));
    MiddleLeftWheel.Value()->RotateRelative(glm::vec3(rotation, 0.0f, 0.0f));
    MiddleRightWheel.Value()->RotateRelative(glm::vec3(-rotation, 0.0f, 0.0f));
    BackLeftWheel.Value()->RotateRelative(glm::vec3(rotation, 0.0f, 0.0f));
    BackRightWheel.Value()->RotateRelative(glm::vec3(-rotation, 0.0f, 0.0f));


    m_PrevSteer = m_Vehicle->getWheelInfo(0).m_steering;
}

void Vehicle::Destroy() {
    Object().Scene().RemoveVehicle(m_Vehicle);

    delete m_VehicleRaycaster;
    delete m_Vehicle;
}

void Vehicle::ApplyEngineForce(float force) {
    m_Vehicle->applyEngineForce(force, 0);
    m_Vehicle->applyEngineForce(force, 1);
}

void Vehicle::Brake(float brake) {
    m_Vehicle->setBrake(brake, 2);
    m_Vehicle->setBrake(brake, 3);
}

void Vehicle::Steer(float steering) {
    m_Vehicle->setSteeringValue(steering, 0);
    m_Vehicle->setSteeringValue(steering, 1);
}
