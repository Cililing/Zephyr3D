#include "PhysicsRenderer.h"

zephyr::physics::PhysicsRenderer::PhysicsRenderer(zephyr::rendering::DrawManager& draw_manager)
    : m_DebugMode(0) {
    m_DebugShader = (zephyr::rendering::Debug*)draw_manager.Shader("Debug");
}

void zephyr::physics::PhysicsRenderer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    m_DebugShader->DrawLine(Vector3(from), Vector3(to), Vector3(color));
}

void zephyr::physics::PhysicsRenderer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3&, const btVector3&, const btVector3&, const btVector3& color, btScalar alpha) {
    drawTriangle(v0, v1, v2, color, alpha);
}

void zephyr::physics::PhysicsRenderer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar) {
    m_DebugShader->DrawTriangle(Vector3(v0), Vector3(v1), Vector3(v2), Vector3(color));
}

void zephyr::physics::PhysicsRenderer::drawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& trans, const btVector3& color) {
    m_DebugShader->DrawPlane(Vector3(trans.getOrigin()), Vector3(planeNormal), planeConst, Vector3(color));
}

void zephyr::physics::PhysicsRenderer::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color) {
    glm::vec3 col(color.getX(), color.getY(), color.getZ());
    glm::mat4 transform = glm::scale(glm::mat4(1.0f), Vector3(bbMax - bbMin));

    m_DebugShader->DrawCube(transform, Vector3(color));
}

void zephyr::physics::PhysicsRenderer::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color) {
    float tmp[16];
    trans.getOpenGLMatrix(tmp);
    glm::mat4 transform = glm::make_mat4(tmp);
    transform = glm::scale(transform, Vector3(bbMax - bbMin));

    m_DebugShader->DrawCube(transform, Vector3(color));
}

void zephyr::physics::PhysicsRenderer::reportErrorWarning(const char* warningString) {
    ERROR_LOG(Logger::ESender::Physics, "%s", warningString);
}

void zephyr::physics::PhysicsRenderer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {
    ERROR_LOG(Logger::ESender::Physics, "drawContactPoint not implemented yet");
}

void zephyr::physics::PhysicsRenderer::draw3dText(const btVector3& location, const char* textString) {
    ERROR_LOG(Logger::ESender::Physics, "draw3dText not implemented yet");
}

void zephyr::physics::PhysicsRenderer::setDebugMode(int debugMode) {
    m_DebugMode = debugMode;
}

int zephyr::physics::PhysicsRenderer::getDebugMode() const {
    return m_DebugMode;
}

