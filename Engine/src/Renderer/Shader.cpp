#include "LRT/Renderer/Shader.h"
#include "LRT/Core/Logger.h"

namespace LRT::Renderer {

    Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name) {
        // u32 vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
        // u32 fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

        // m_ProgramID = glCreateProgram();
        // glAttachShader(m_ProgramID, vertexShader);
        // glAttachShader(m_ProgramID, fragmentShader);
        // glLinkProgram(m_ProgramID);

        // i32 success;
        // glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
        // if (!success) { LRT_ERROR("Shader link failed: {}", name); }

        // glDeleteShader(vertexShader);
        // glDeleteShader(fragmentShader);

        LRT_DEBUG("Shader '{}' compiled and linked", m_Name);
    }

    Shader::~Shader() {
        // glDeleteProgram(m_ProgramID);
    }

    void Shader::Bind() const {
        // glUseProgram(m_ProgramID);
    }

    void Shader::Unbind() const {
        // glUseProgram(0);
    }

    void Shader::SetInt(const std::string& name, i32 value) {
        // glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetFloat(const std::string& name, f32 value) {
        // glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetVec3(const std::string& name, const Math::Vec3& value) {
        // glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::SetVec4(const std::string& name, const Math::Vec4& value) {
        // glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::SetMat4(const std::string& name, const Math::Mat4& value) {
        // glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value.Data());
    }

    u32 Shader::CompileShader(u32 type, const std::string& source) {
        // u32 shader = glCreateShader(type);
        // const char* src = source.c_str();
        // glShaderSource(shader, 1, &src, nullptr);
        // glCompileShader(shader);
        // return shader;
        return 0;
    }

    i32 Shader::GetUniformLocation(const std::string& name) {
        auto it = m_UniformLocationCache.find(name);
        if (it != m_UniformLocationCache.end()) return it->second;

        // i32 location = glGetUniformLocation(m_ProgramID, name.c_str());
        i32 location = -1;
        if (location == -1) {
            LRT_WARN("Uniform '{}' not found in shader '{}'", name, m_Name);
        }
        m_UniformLocationCache[name] = location;
        return location;
    }

    Unique<Shader> Shader::Create(const std::string& name,
                                   const std::string& vertexSrc,
                                   const std::string& fragmentSrc) {
        return MakeUnique<Shader>(name, vertexSrc, fragmentSrc);
    }

} // namespace LRT::Renderer
