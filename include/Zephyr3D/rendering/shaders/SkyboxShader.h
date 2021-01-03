#ifndef Skybox_h
#define Skybox_h

#include "../ShaderProgram.h"
#include "../ICamera.h"
#include "../Cubemap.h"

namespace zephyr::rendering {

class SkyboxShader : public ShaderProgram {
public:
    SkyboxShader()
        : ShaderProgram(
            "Skybox",
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/SkyboxVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/SkyboxFrag.glsl"),
            "") { }

    SkyboxShader(const SkyboxShader&) = delete;
    SkyboxShader& operator=(const SkyboxShader&) = delete;
    SkyboxShader(SkyboxShader&&) = delete;
    SkyboxShader& operator=(SkyboxShader&&) = delete;
    ~SkyboxShader() = default;

    void SkyboxCubemap(const resources::Image& right, const resources::Image& left, const resources::Image& top, const resources::Image& bottom, const resources::Image& back, const resources::Image& front) {
        m_Cubemap = std::make_unique<Cubemap>(right, left, top, bottom, back, front);
    }

    void Draw(const ICamera* camera) override {
        if (m_Cubemap == nullptr) {
            return;
        }

        glDepthFunc(GL_LEQUAL);

        glm::mat4 pv = camera->Projection() * glm::mat4(glm::mat3(camera->View()));
        Uniform("pv", pv);
        m_Cubemap->Draw(*this);

        glDepthFunc(GL_LESS);
    }

private:
    std::unique_ptr<Cubemap> m_Cubemap{ nullptr };
};

}

#endif
