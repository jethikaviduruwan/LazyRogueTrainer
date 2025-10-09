#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Math/Vec3.h"
#include "LRT/Math/Vec4.h"
#include "LRT/Math/Mat4.h"
#include <string>
#include <unordered_map>

namespace LRT::Renderer {

    class Shader {
    public:
        Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        LRT_NON_COPYABLE(Shader)

        void Bind() const;
        void Unbind() const;

        void SetInt(const std::string& name, i32 value);
        void SetFloat(const std::string& name, f32 value);
        void SetVec3(const std::string& name, const Math::Vec3& value);
        void SetVec4(const std::string& name, const Math::Vec4& value);
        void SetMat4(const std::string& name, const Math::Mat4& value);

        const std::string& GetName() const { return m_Name; }
        u32 GetProgramID() const { return m_ProgramID; }

        static Unique<Shader> Create(const std::string& name,
                                     const std::string& vertexSrc,
                                     const std::string& fragmentSrc);

    private:
        u32 CompileShader(u32 type, const std::string& source);
        i32 GetUniformLocation(const std::string& name);

        u32 m_ProgramID = 0;
        std::string m_Name;
        std::unordered_map<std::string, i32> m_UniformLocationCache;
    };

} // namespace LRT::Renderer
