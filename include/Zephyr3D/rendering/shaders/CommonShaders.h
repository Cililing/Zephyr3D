#ifndef CommonShaders_h
#define CommonShaders_h

#include "../Primitives.h"

#pragma warning(push, 0)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#pragma warning(pop)

#include <iostream>
#include <vector>
#include <tuple>

namespace zephyr::rendering {

class Phong : public ShaderProgram {
public:
    Phong()
        : ShaderProgram(
            "Phong",
            ShaderProgram::ETrait::Position | ShaderProgram::ETrait::Normal | ShaderProgram::ETrait::TexCoord,
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PhongFrag.glsl"),
            "") { }

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
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PureColorVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PureColorFrag.glsl"),
            "") { }

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
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PureTextureVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/PureTextureFrag.glsl"),
            "") { }

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
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/SkyboxVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/SkyboxFrag.glsl"),
            "") { }

    Skybox(const Skybox&) = delete;
    Skybox& operator=(const Skybox&) = delete;
    Skybox(Skybox&&) = delete;
    Skybox& operator=(Skybox&&) = delete;
    ~Skybox() = default;
};

class Debug : public ShaderProgram {
public:
    Debug()
        : ShaderProgram(
            "Debug",
            ShaderProgram::ETrait::Position | ShaderProgram::ETrait::Color,
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/DebugVert.glsl"),
            ReadShaderFile("../../include/Zephyr3D/rendering/shaders/DebugFrag.glsl"),
            "") {
    }

    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;
    Debug(Debug&&) = delete;
    Debug& operator=(Debug&&) = delete;
    ~Debug() = default;

    void CallDraws() override {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        DrawLines();

        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
        // All calculation are made with assumption that prefab line define points <origin, (1, 0, 0)>
        const glm::vec3 prefab_end(1.0f, 0.0f, 0.0f);

        // Translation to move new line from it's position to origin
        glm::vec3 translation = -start;

        // Calculate angle matrix between prefab line and translated new line
        // Move line to the origin, no needs to create start_prime
        glm::vec3 end_prime = glm::normalize(end + translation);
        glm::quat rot = glm::rotation(prefab_end, end_prime);
        glm::mat4 rotation = glm::toMat4(rot);

        // Lengths ratio equals to new line magnitude because prefab line has legnth 1
        float length = glm::length((end - start));

        // Create model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), -translation);
        model = model * rotation;
        model = glm::scale(model, glm::vec3(length));

        m_Lines.emplace_back(model, color);
    }

private:
    // Prefabs
    Line m_Line;
    std::vector<std::pair<glm::mat4, glm::vec3>> m_Lines;

    void DrawLines() {
        constexpr auto element_size = sizeof(m_Lines[0]);

        // Bind vertex array
        glBindVertexArray(m_Line.VAO());

        // Prepare instance instance_buffer
        GLuint instance_buffer;
        glGenBuffers(1, &instance_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
        glBufferData(GL_ARRAY_BUFFER, element_size * m_Lines.size(), &m_Lines[0], GL_STATIC_DRAW);

        // Add model
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, element_size, (void*)(0));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, element_size, (void*)(1 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, element_size, (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, element_size, (void*)(3 * sizeof(glm::vec4)));

        // Add color
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, element_size, (void*)(sizeof(glm::mat4)));

        // Divisors
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);

        // Drawing
        glDrawArraysInstanced(GL_LINES, 0, 2, m_Lines.size());

        // Cleanup
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteBuffers(1, &instance_buffer);
        m_Lines.clear();
    }
};

}

#endif
