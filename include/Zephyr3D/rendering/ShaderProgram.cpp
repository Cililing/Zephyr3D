#include "ShaderProgram.h"

#include "../core/debugging/Logger.h"

zephyr::rendering::ShaderProgram::ShaderProgram(const std::string& name, const std::string& vertex_path, const std::string& fragment_path, const std::string& geometry_path)
    : m_Name(name) {
    m_ID = glCreateProgram();

    auto vertex_shader = CompileShader(vertex_path, GL_VERTEX_SHADER);
    auto fragment_shader = CompileShader(fragment_path, GL_FRAGMENT_SHADER);
    auto geometry_shader = !geometry_path.empty() ? CompileShader(geometry_path, GL_GEOMETRY_SHADER) : 0;

    assert(vertex_shader != 0 && fragment_shader != 0);

    LinkProgram();

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glDeleteShader(geometry_shader);
}

zephyr::rendering::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_ID);
}

void zephyr::rendering::ShaderProgram::Use() const {
    glUseProgram(m_ID);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, const glm::vec2 &vec) const {
    glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &vec[0]);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, const glm::vec3 &vec) const {
    glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &vec[0]);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, const glm::vec4 &vec) const {
    glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &vec[0]);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void zephyr::rendering::ShaderProgram::Uniform(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

std::string zephyr::rendering::ShaderProgram::ReadShaderFile(const std::string& path) {
    std::fstream shader_file;
    std::stringstream shader_stream;

    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Read file
    try {
        shader_file.open(path);
        shader_stream << shader_file.rdbuf();
        shader_file.close();
    }
    catch (const std::ifstream::failure & e) {
        ERROR_LOG(Logger::ESender::Rendering, "Failed to read shader file %s:\n%s", path, e.what());
        return "";
    }

    return shader_stream.str();
}

GLuint zephyr::rendering::ShaderProgram::CompileShader(const std::string& code, GLenum shader_type) {
    // Compile shader
    GLuint shader = glCreateShader(shader_type);
    const GLchar* shader_code_ptr = code.c_str();
    glShaderSource(shader, 1, &shader_code_ptr, nullptr);
    glCompileShader(shader);
    
    // Check compile errors
    GLint success;
    GLchar info_log[infolog_max_length];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, infolog_max_length, nullptr, info_log);
        ERROR_LOG(Logger::ESender::Rendering, "Failed to compile shader %d:\n%s", shader_type, info_log);
        return 0;
    }
    
    glAttachShader(m_ID, shader);
    
    return shader;
}

void zephyr::rendering::ShaderProgram::LinkProgram() {
    glLinkProgram(m_ID);
    
    // Check linking errors
    GLint success;
    GLchar info_log[infolog_max_length];
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, infolog_max_length, nullptr, info_log);
        ERROR_LOG(Logger::ESender::Rendering, "Failed to link shader %d:\n%s", m_ID, info_log);
    }
}
