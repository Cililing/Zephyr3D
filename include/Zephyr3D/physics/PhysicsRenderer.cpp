#include "PhysicsRenderer.h"

PhysicsRenderer::PhysicsRenderer(zephyr::rendering::DrawManager& draw_manager)
    : m_DebugMode(0) {
    m_DebugShader = (zephyr::rendering::Debug*)draw_manager.Shader("Debug");
}

void PhysicsRenderer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    glm::vec3 start(from.getX(), from.getY(), from.getZ());
    glm::vec3 end(to.getX(), to.getY(), to.getZ());
    glm::vec3 col(color.getX(), color.getY(), color.getZ());

    m_DebugShader->DrawLine(start, end, col);
}

void PhysicsRenderer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3&, const btVector3&, const btVector3&, const btVector3& color, btScalar alpha) {
    drawTriangle(v0, v1, v2, color, alpha);
}

void PhysicsRenderer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar) {
    glm::vec3 col(color.getX(), color.getY(), color.getZ());
    glm::vec3 upper(v0.getX(), v0.getY(), v0.getZ());
    glm::vec3 lower_left(v1.getX(), v1.getY(), v1.getZ());
    glm::vec3 lower_right(v2.getX(), v2.getY(), v2.getZ());

    m_DebugShader->DrawTriangle(upper, lower_left, lower_right, col);
}

void PhysicsRenderer::drawPlane(const btVector3& planeNormal, btScalar planeConst, const btTransform& trans, const btVector3& color) {
    glm::vec3 col(color.getX(), color.getY(), color.getZ());

    auto bt_pos = trans.getOrigin();
    glm::vec3 position(bt_pos.getX(), bt_pos.getY(), bt_pos.getZ());

    glm::vec3 normal(planeNormal.getX(), planeNormal.getY(), planeNormal.getZ());

    m_DebugShader->DrawPlane(position, normal, planeConst, col);
}

void PhysicsRenderer::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btVector3& color) {
    glm::vec3 col(color.getX(), color.getY(), color.getZ());
    glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(bbMax.getX() - bbMin.getX(), bbMax.getY() - bbMin.getY(), bbMax.getZ() - bbMin.getZ()));

    m_DebugShader->DrawCuboid(transform, col);
}

void PhysicsRenderer::drawBox(const btVector3& bbMin, const btVector3& bbMax, const btTransform& trans, const btVector3& color) {
    glm::vec3 col(color.getX(), color.getY(), color.getZ());
    
    float tmp[16];
    trans.getOpenGLMatrix(tmp);
    glm::mat4 transform = glm::make_mat4(tmp);
    transform = glm::scale(transform, glm::vec3(bbMax.getX() - bbMin.getX(), bbMax.getY() - bbMin.getY(), bbMax.getZ() - bbMin.getZ()));

    m_DebugShader->DrawCuboid(transform, col);
}

void PhysicsRenderer::reportErrorWarning(const char* warningString) {
    ERROR_LOG(Logger::ESender::Physics, "%s", warningString);
}

void PhysicsRenderer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {
    ERROR_LOG(Logger::ESender::Physics, "drawContactPoint not implemented yet");
}

void PhysicsRenderer::draw3dText(const btVector3& location, const char* textString) {
    ERROR_LOG(Logger::ESender::Physics, "draw3dText not implemented yet");
}

void PhysicsRenderer::setDebugMode(int debugMode) {
    m_DebugMode = debugMode;
}

int PhysicsRenderer::getDebugMode() const {
    return m_DebugMode;
}

