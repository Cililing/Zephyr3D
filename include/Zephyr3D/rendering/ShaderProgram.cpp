#include "ShaderProgram.h"

#include "IDrawable.h"
#include "IShaderProperty.h"

zephyr::rendering::ShaderProgram::ShaderProgram(const std::string& name, ETrait traits, const std::string& vertex_path, const std::string& fragment_path, const std::string& geometry_path)
    : m_Traits(ETrait::None)
    , m_Name(name) {
    m_ID = glCreateProgram();

    unsigned int vertex_shader = CompileShader(vertex_path, GL_VERTEX_SHADER);
    unsigned int fragment_shader = CompileShader(fragment_path, GL_FRAGMENT_SHADER);
    unsigned int geometry_shader = geometry_path != "" ? CompileShader(geometry_path, GL_GEOMETRY_SHADER) : -1;

    // Either vertex and fragment shaders are mandatory
    assert(vertex_shader != -1 && fragment_shader != -1);

    LinkProgram();

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    if (geometry_shader != -1) {
        glDeleteShader(geometry_shader);
    }
}

zephyr::rendering::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_ID);
}

void zephyr::rendering::ShaderProgram::Use() const {
    glUseProgram(m_ID);
}

void zephyr::rendering::ShaderProgram::RegisterDrawCall(const IDrawable* drawable) {
    // Ensure that each component is registered at most once
    assert(std::find(m_Drawables.begin(), m_Drawables.end(), drawable) == m_Drawables.end());

    m_Drawables.push_back(drawable);
}

void zephyr::rendering::ShaderProgram::UnregisterDrawCall(const IDrawable* drawable) {
    // Unregistering not registered component has no effect
    auto to_erase = std::find(m_Drawables.begin(), m_Drawables.end(), drawable);
    if (to_erase != m_Drawables.end()) {
        m_Drawables.erase(to_erase);
    }
}

void zephyr::rendering::ShaderProgram::RegisterShaderProperty(const IShaderProperty* property) {
    // Ensure that each component is registered at most once
    assert(std::find(m_Properties.begin(), m_Properties.end(), property) == m_Properties.end());

    m_Properties.push_back(property);
}

void zephyr::rendering::ShaderProgram::UnregisterShaderProperty(const IShaderProperty* property) {
    // Unregistering not registered component has no effect
    auto to_erase = std::find(m_Properties.begin(), m_Properties.end(), property);
    if (to_erase != m_Properties.end()) {
        m_Properties.erase(to_erase);
    }
}

void zephyr::rendering::ShaderProgram::CallProperties() {
    for (auto& property : m_Properties) {
        property->SetProperty(*this);
    }
}

void zephyr::rendering::ShaderProgram::CallDraws() {
    for (auto& drawable : m_Drawables) {
        drawable->Draw(*this);
    }
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

unsigned int zephyr::rendering::ShaderProgram::CompileShader(std::string code, GLenum shader_type) {
    // Compile shader
    unsigned int shader = glCreateShader(shader_type);
    const char *shader_code_ptr = code.c_str();
    glShaderSource(shader, 1, &shader_code_ptr, nullptr);
    glCompileShader(shader);
    
    // Check compile errors
    GLint success;
    GLchar info_log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, info_log);
        ERROR_LOG(Logger::ESender::Rendering, "Failed to compile shader %d:\n%s", shader_type, info_log);
        return -1;
    }
    
    glAttachShader(m_ID, shader);
    
    return shader;
}

void zephyr::rendering::ShaderProgram::LinkProgram() {
    glLinkProgram(m_ID);
    
    // Check linking errors
    int success;
    char info_log[1024];
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ID, 1024, nullptr, info_log);
        Logger::Instance().ErrorLog(Logger::ESender::Rendering, "Failed to link shader %d:\n%s", m_ID, info_log);
    }
}
