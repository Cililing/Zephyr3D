#ifndef Skybox_h
#define Skybox_h

#include "../ShaderProgram.h"

namespace zephyr::rendering {

class Skybox : public ShaderProgram {
public:
    Skybox()
        : ShaderProgram(
            "Skybox",
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/SkyboxVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/SkyboxFrag.glsl"),
            "") { }

    Skybox(const Skybox&) = delete;
    Skybox& operator=(const Skybox&) = delete;
    Skybox(Skybox&&) = delete;
    Skybox& operator=(Skybox&&) = delete;
    ~Skybox() = default;
};

}

#endif
