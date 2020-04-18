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

void PhysicsRenderer::setDebugMode(int debugMode) {
    m_DebugMode = debugMode;
}

int PhysicsRenderer::getDebugMode() const {
    return m_DebugMode;
}

