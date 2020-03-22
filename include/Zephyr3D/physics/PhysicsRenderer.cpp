#include "PhysicsRenderer.h"

PhysicsRenderer::PhysicsRenderer(DrawManager& draw_manager)
    : m_DrawManager(draw_manager) {
}

void PhysicsRenderer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    glm::vec3 start(from.getX(), from.getY(), from.getZ());
    glm::vec3 end(to.getX(), to.getY(), to.getZ());
    glm::vec3 col(color.getX(), color.getY(), color.getZ());

    m_DrawManager.DrawLine(start, end, col);
}

void PhysicsRenderer::reportErrorWarning(const char* warningString) {
    ERROR_LOG(Logger::ESender::Physics, "%s", warningString);
}

