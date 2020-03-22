#ifndef PhysicsRenderer_h
#define PhysicsRenderer_h

#include "../rendering/DrawManager.h"
#include "../debuging/Logger.h"

#include <LinearMath/btIDebugDraw.h>

class PhysicsRenderer : public btIDebugDraw {
public:
    PhysicsRenderer(DrawManager& draw_manager);

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

    void reportErrorWarning(const char* warningString) override;

    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {
        (void)PointOnB; (void)normalOnB; (void)distance; (void)lifeTime; (void)color;
    }
    void draw3dText(const btVector3& location, const char* textString) override {
        (void)location; (void)textString;
    }
    void setDebugMode(int debugMode) override {
        (void)debugMode;
    }
    int getDebugMode() const override { return 1; }

private:
    DrawManager& m_DrawManager;
};

#endif
