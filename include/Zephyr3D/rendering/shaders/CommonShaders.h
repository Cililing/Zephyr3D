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
    using instance_data = std::vector<std::pair<glm::mat4 /*transform*/, glm::vec3 /*color*/>>;

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
        DrawLines();
        DrawPlanes();
        DrawCuboids();
    }

    void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color) {
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

    void DrawPlane(const glm::mat4& transform, const glm::vec3& color) {
        m_Planes.emplace_back(transform, color);
    }

    void DrawPlane(const glm::vec3& position, const glm::vec3& normal, float constant, const glm::vec3& color) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = transform * glm::toMat4(glm::quat(normal, glm::vec3(0.0f, 0.0f, 1.0f)));
        transform = glm::scale(transform, glm::vec3(constant));

        m_Planes.emplace_back(transform, color);
    }

    void DrawCuboid(const glm::mat4& transform, const glm::vec3& color) {
        m_Cuboids.emplace_back(transform, color);
    }

private:
    const static GLsizei s_ElementSize = sizeof(instance_data::value_type);

    // Prefabs
    Line m_LinePrefab;
    Plane m_PlanePrefab;
    Cuboid m_CuboidPrefab;

    //
    instance_data m_Lines;
    instance_data m_Planes;
    instance_data m_Cuboids;

    void DrawLines() {
        GLuint buffer = PrepareBuffer(m_LinePrefab.VAO(), m_Lines);

        glBindVertexArray(m_LinePrefab.VAO());
        glDrawArraysInstanced(GL_LINES, 0, 2, m_Lines.size());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteBuffers(1, &buffer);
        m_Lines.clear();
    }

    void DrawPlanes() {
        GLuint buffer = PrepareBuffer(m_PlanePrefab.VAO(), m_Planes);

        glBindVertexArray(m_PlanePrefab.VAO());
        glDrawArraysInstanced(GL_LINE_STRIP, 0, 5, m_Planes.size());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteBuffers(1, &buffer);
        m_Planes.clear();
    }

    void DrawCuboids() {
        GLuint buffer = PrepareBuffer(m_CuboidPrefab.VAO(), m_Cuboids);

        glBindVertexArray(m_CuboidPrefab.VAO());
        glDrawArraysInstanced(GL_LINE_STRIP, 0, 17, m_Cuboids.size());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteBuffers(1, &buffer);
        m_Cuboids.clear();
    }

    GLuint PrepareBuffer(GLuint vao, const instance_data& data) {
        glBindVertexArray(vao);

        // Prepare instance instance_buffer
        GLuint instance_buffer;
        glGenBuffers(1, &instance_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
        glBufferData(GL_ARRAY_BUFFER, s_ElementSize * data.size(), &data[0], GL_STATIC_DRAW);

        // Add model
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, s_ElementSize, (void*)(0));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, s_ElementSize, (void*)(1 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, s_ElementSize, (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, s_ElementSize, (void*)(3 * sizeof(glm::vec4)));

        // Add color
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, s_ElementSize, (void*)(sizeof(glm::mat4)));

        // Divisors
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return instance_buffer;
    }
};

}

#endif
