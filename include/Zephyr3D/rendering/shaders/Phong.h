#ifndef Phong_h
#define Phong_h

#include "../ShaderProgram.h"

namespace zephyr::rendering {

class Phong : public ShaderProgram {
public:
    Phong()
        : ShaderProgram(
            "Phong",
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongFrag.glsl"),
            "") { }

    Phong(const Phong&) = delete;
    Phong& operator=(const Phong&) = delete;
    Phong(Phong&&) = delete;
    Phong& operator=(Phong&&) = delete;
    ~Phong() = default;
};

}

#endif
