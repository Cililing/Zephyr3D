#ifndef PhysicsRenderer_h
#define PhysicsRenderer_h

#include "../rendering/DrawManager.h"
#include "../debuging/Logger.h"
#include "../core/Math.h"

#pragma warning(push, 0)
#include <LinearMath/btIDebugDraw.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(pop)

namespace zephyr::physics {

class PhysicsRenderer : public btIDebugDraw {
public:
    PhysicsRenderer(zephyr::rendering::DrawManager& draw_manager);

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
    void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, [[maybe_unused]] const btVector3& /*n0*/, [[maybe_unused]] const btVector3& /*n1*/, [[maybe_unused]] const btVector3& /*n2*/, const btVector3& color, btScalar alpha) override;
    void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, [[maybe_unused]] btScalar /*alpha*/) override;
    void drawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& trans, const btVector3& color) override;
    void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color) override;
    void drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color) override;

    void reportErrorWarning(const char* warningString) override;
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
    void draw3dText(const btVector3& location, const char* textString) override;

    void setDebugMode(int debugMode) override;
    int getDebugMode() const override;

private:
    int m_DebugMode;
    zephyr::rendering::Debug* m_DebugShader;
};

}

#endif
