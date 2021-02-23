#ifndef ShaderProgram_h
#define ShaderProgram_h

#pragma warning(push, 0)
#include <glad/glad.h>
#include <glm/glm.hpp>
#pragma warning(pop)

#include <assert.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

constexpr GLsizei infolog_max_length = 1024;

namespace zephyr::rendering {

class ICamera;

class ShaderProgram {
public:
    ShaderProgram(const std::string& name, const std::string& vertex_code, const std::string& fragment_code, const std::string& geometry_code);

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&&) = delete;
    ShaderProgram& operator=(ShaderProgram&&) = delete;
    virtual ~ShaderProgram();

    void Use() const;

    GLuint ID() const { return m_ID; }
    const std::string& Name() const { return m_Name; }

    virtual void Draw(const ICamera* camera) = 0;

    void Uniform(const std::string &name, bool value) const;
    void Uniform(const std::string &name, int value) const;
    void Uniform(const std::string &name, float value) const;
    void Uniform(const std::string &name, const glm::vec2 &vec) const;
    void Uniform(const std::string &name, float x, float y) const;
    void Uniform(const std::string &name, const glm::vec3 &vec) const;
    void Uniform(const std::string &name, float x, float y, float z) const;
    void Uniform(const std::string &name, const glm::vec4 &vec) const;
    void Uniform(const std::string &name, float x, float y, float z, float w) const;
    void Uniform(const std::string &name, const glm::mat2 &mat) const;
    void Uniform(const std::string &name, const glm::mat3 &mat) const;
    void Uniform(const std::string &name, const glm::mat4 &mat) const;

protected:
    std::string ReadShaderFile(const std::string& path);

private:
    GLuint m_ID;
    std::string m_Name;

    void LinkProgram();
    GLuint CompileShader(const std::string& code, GLenum shader);
};

}

#endif
