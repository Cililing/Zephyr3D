#ifndef ShaderProgram_h
#define ShaderProgram_h

#include "../debuging/Logger.h"
#include "../core/Enum.h"

#pragma warning(push, 0)
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <assert.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#pragma warning(pop)

namespace zephyr::rendering {

class IDrawable;
class IShaderProperty;

class ShaderProgram {
public:
    enum class ETrait : unsigned char {
        None = 0,
        Position = 1 << 0,
        Normal = 1 << 1,
        TexCoord = 1 << 2,
        Color = 1 << 3
    };

    ShaderProgram(const std::string& name);
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&&) = delete;
    ShaderProgram& operator=(ShaderProgram&&) = delete;
    ~ShaderProgram();
    
    void AttachShaders(const char *vertex_path, const char *fragment_path, const char *geometry_path = nullptr);
    void Use() const;

    GLuint ID() const { return m_ID; }
    std::string Name() const { return m_Name; }

    ETrait Traits() const { return m_Traits; }
    void Traits(ETrait traits) { m_Traits = traits; }

    void RegisterDrawCall(const IDrawable* drawable);
    void UnregisterDrawCall(const IDrawable* drawable);

    void RegisterShaderProperty(const IShaderProperty* property);
    void UnregisterShaderProperty(const IShaderProperty* property);

    void CallProperties() const;
    void CallDraws() const;

    // Setters for OpenGL shaders
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

private:
    void LinkProgram();
    unsigned int AttachShader(const char *path, GLenum shader);

    GLuint m_ID;
    ETrait m_Traits;
    std::string m_Name;
    std::vector<const IDrawable*> m_Drawables;
    std::vector<const IShaderProperty*> m_Properties;
};

ENABLE_BITMASK_OPERATORS(ShaderProgram::ETrait);

}

#endif
