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
        PrepareVAO(m_Line.VAO());
    }

    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;
    Debug(Debug&&) = delete;
    Debug& operator=(Debug&&) = delete;
    ~Debug() = default;

    void CallDraws() override {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        DrawLines();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void DrawLine(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
        // All calculation are made with assumption that prefab line define points <origin, (1, 0, 0)>
        
        // Translation to move new line from it's position to origin
        glm::vec3 translation = -start;

        // Move line to the origin, no needs to create start_prime
        glm::vec3 end_prime = end + translation;

        // Calculate angle matrix between prefab line and translated new line
        glm::vec3 v = glm::vec3(0.0f, -end_prime.z, end_prime.y);
        float angle = acos(end_prime.x / glm::length(end_prime));
        glm::mat4 rotation = glm::rotate(angle, v);

        // Lengths ratio equals to new line magnitude because prefab line has legnth 1
        float length = glm::length((end - start));

        // Create model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), -translation);
        model = model * rotation;
        model = glm::scale(model, glm::vec3(length));
        
        glm::vec3 start_t = model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec3 end_t = model * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

        std::cout << "Effect:\n";
        std::cout << start_t.x << ' ' << start_t.y << ' ' << start_t.z << '\n';
        std::cout << end_t.x << ' ' << end_t.y << ' ' << end_t.z << "\n\n";

        m_Lines.emplace_back(model, color);
    }

private:
    // Prefabs
    Line m_Line;

    //                    model      color
    std::vector<std::pair<glm::mat4, glm::vec3>> m_Lines;

    void PrepareVAO(GLuint vao) {
        glBindVertexArray(vao);

        // Add color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        // Add model
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        //Divisor
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);

        glBindVertexArray(0);
    }

    void DrawLines() {
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, m_Lines.size() * (sizeof(glm::vec3) + sizeof(glm::mat4)), &m_Lines[0], GL_STATIC_DRAW);

        glBindVertexArray(m_Line.VAO());
        glDrawElementsInstanced(GL_LINE, 2, GL_UNSIGNED_INT, 0, m_Lines.size());
        glBindVertexArray(0);
        m_Lines.clear();
    }
};

}

#endif
