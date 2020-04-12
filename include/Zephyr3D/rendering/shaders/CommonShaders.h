#ifndef CommonShaders_h
#define CommonShaders_h

#include "../ShaderProgram.h"

namespace zephyr::rendering {

class Phong : public ShaderProgram {
public:
    Phong()
        : ShaderProgram(
            "Phong",
            ShaderProgram::ETrait::Position | ShaderProgram::ETrait::Normal | ShaderProgram::ETrait::TexCoord,
            "../../include/Zephyr3D/rendering/shaders/PhongVert.glsl",
            "../../include/Zephyr3D/rendering/shaders/PhongFrag.glsl"
        ) { }

    Phong(const Phong&) = delete;
    Phong& operator=(const Phong&) = delete;
    Phong(Phong&&) = delete;
    Phong& operator=(Phong&&) = delete;
    ~Phong() = default;
};


class PureColor : public ShaderProgram {
public:
    PureColor()
        : ShaderProgram(
            "PureColor",
            ShaderProgram::ETrait::Position | ShaderProgram::ETrait::Color,
            "../../include/Zephyr3D/rendering/shaders/PureColorVert.glsl",
            "../../include/Zephyr3D/rendering/shaders/PureColorFrag.glsl"
        ) { }

    PureColor(const PureColor&) = delete;
    PureColor& operator=(const PureColor&) = delete;
    PureColor(PureColor&&) = delete;
    PureColor& operator=(PureColor&&) = delete;
    ~PureColor() = default;
};


class PureTexture : public ShaderProgram {
public:
    PureTexture()
        : ShaderProgram(
            "PureTexture",
            ShaderProgram::ETrait::Position | ShaderProgram::ETrait::TexCoord,
            "../../include/Zephyr3D/rendering/shaders/PureTextureVert.glsl",
            "../../include/Zephyr3D/rendering/shaders/PureTextureFrag.glsl"
        ) { }

    PureTexture(const PureTexture&) = delete;
    PureTexture& operator=(const PureTexture&) = delete;
    PureTexture(PureTexture&&) = delete;
    PureTexture& operator=(PureTexture&&) = delete;
    ~PureTexture() = default;
};


class Skybox : public ShaderProgram {
public:
    Skybox()
        : ShaderProgram(
            "Skybox",
            ShaderProgram::ETrait::Position,
            "../../include/Zephyr3D/rendering/shaders/SkyboxVert.glsl",
            "../../include/Zephyr3D/rendering/shaders/SkyboxFrag.glsl"
        ) { }

    Skybox(const Skybox&) = delete;
    Skybox& operator=(const Skybox&) = delete;
    Skybox(Skybox&&) = delete;
    Skybox& operator=(Skybox&&) = delete;
    ~Skybox() = default;
};


}

#endif
