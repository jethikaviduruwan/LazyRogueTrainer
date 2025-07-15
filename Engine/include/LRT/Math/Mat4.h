#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Math/Vec3.h"
#include "LRT/Math/Vec4.h"
#include <cmath>
#include <array>

namespace LRT::Math {

    struct Mat4 {
        // Column-major storage (OpenGL convention)
        std::array<f32, 16> m{};

        constexpr Mat4() = default;

        static constexpr Mat4 Identity() {
            Mat4 result;
            result.m[0]  = 1.0f;
            result.m[5]  = 1.0f;
            result.m[10] = 1.0f;
            result.m[15] = 1.0f;
            return result;
        }

        f32& operator()(u32 row, u32 col) { return m[col * 4 + row]; }
        f32 operator()(u32 row, u32 col) const { return m[col * 4 + row]; }

        Mat4 operator*(const Mat4& rhs) const {
            Mat4 result;
            for (u32 col = 0; col < 4; ++col) {
                for (u32 row = 0; row < 4; ++row) {
                    f32 sum = 0.0f;
                    for (u32 k = 0; k < 4; ++k) {
                        sum += (*this)(row, k) * rhs(k, col);
                    }
                    result(row, col) = sum;
                }
            }
            return result;
        }

        Vec4 operator*(const Vec4& v) const {
            return {
                m[0]*v.x + m[4]*v.y + m[8]*v.z  + m[12]*v.w,
                m[1]*v.x + m[5]*v.y + m[9]*v.z  + m[13]*v.w,
                m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]*v.w,
                m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]*v.w
            };
        }

        const f32* Data() const { return m.data(); }

        static Mat4 Translate(const Vec3& translation) {
            Mat4 result = Identity();
            result.m[12] = translation.x;
            result.m[13] = translation.y;
            result.m[14] = translation.z;
            return result;
        }

        static Mat4 Scale(const Vec3& scale) {
            Mat4 result;
            result.m[0]  = scale.x;
            result.m[5]  = scale.y;
            result.m[10] = scale.z;
            result.m[15] = 1.0f;
            return result;
        }

        static Mat4 RotateZ(f32 radians) {
            Mat4 result = Identity();
            f32 c = std::cos(radians);
            f32 s = std::sin(radians);
            result.m[0] = c;  result.m[4] = -s;
            result.m[1] = s;  result.m[5] = c;
            return result;
        }

        static Mat4 RotateY(f32 radians) {
            Mat4 result = Identity();
            f32 c = std::cos(radians);
            f32 s = std::sin(radians);
            result.m[0] = c;   result.m[8]  = s;
            result.m[2] = -s;  result.m[10] = c;
            return result;
        }

        static Mat4 RotateX(f32 radians) {
            Mat4 result = Identity();
            f32 c = std::cos(radians);
            f32 s = std::sin(radians);
            result.m[5] = c;  result.m[9]  = -s;
            result.m[6] = s;  result.m[10] = c;
            return result;
        }

        static Mat4 Ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
            Mat4 result;
            result.m[0]  =  2.0f / (right - left);
            result.m[5]  =  2.0f / (top - bottom);
            result.m[10] = -2.0f / (far - near);
            result.m[12] = -(right + left) / (right - left);
            result.m[13] = -(top + bottom) / (top - bottom);
            result.m[14] = -(far + near) / (far - near);
            result.m[15] = 1.0f;
            return result;
        }

        static Mat4 Perspective(f32 fovRadians, f32 aspect, f32 near, f32 far) {
            f32 tanHalf = std::tan(fovRadians / 2.0f);
            Mat4 result;
            result.m[0]  = 1.0f / (aspect * tanHalf);
            result.m[5]  = 1.0f / tanHalf;
            result.m[10] = -(far + near) / (far - near);
            result.m[11] = -1.0f;
            result.m[14] = -(2.0f * far * near) / (far - near);
            return result;
        }

        static Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
            Vec3 f = (target - eye).Normalized();
            Vec3 s = f.Cross(up).Normalized();
            Vec3 u = s.Cross(f);

            Mat4 result = Identity();
            result.m[0] = s.x;  result.m[4] = s.y;  result.m[8]  = s.z;
            result.m[1] = u.x;  result.m[5] = u.y;  result.m[9]  = u.z;
            result.m[2] = -f.x; result.m[6] = -f.y; result.m[10] = -f.z;
            result.m[12] = -s.Dot(eye);
            result.m[13] = -u.Dot(eye);
            result.m[14] =  f.Dot(eye);
            return result;
        }
    };

} // namespace LRT::Math
