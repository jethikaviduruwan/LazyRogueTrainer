#pragma once

#include "LRT/Core/Types.h"
#include <cmath>

namespace LRT::Math {

    struct Vec3 {
        f32 x = 0.0f;
        f32 y = 0.0f;
        f32 z = 0.0f;

        constexpr Vec3() = default;
        constexpr Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
        constexpr explicit Vec3(f32 scalar) : x(scalar), y(scalar), z(scalar) {}

        constexpr Vec3 operator+(const Vec3& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
        constexpr Vec3 operator-(const Vec3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
        constexpr Vec3 operator*(f32 scalar) const { return { x * scalar, y * scalar, z * scalar }; }
        constexpr Vec3 operator/(f32 scalar) const { return { x / scalar, y / scalar, z / scalar }; }
        constexpr Vec3 operator-() const { return { -x, -y, -z }; }

        Vec3& operator+=(const Vec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
        Vec3& operator-=(const Vec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
        Vec3& operator*=(f32 scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }

        constexpr f32 Dot(const Vec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

        constexpr Vec3 Cross(const Vec3& rhs) const {
            return {
                y * rhs.z - z * rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x
            };
        }

        f32 Length() const { return std::sqrt(x * x + y * y + z * z); }
        constexpr f32 LengthSquared() const { return x * x + y * y + z * z; }

        Vec3 Normalized() const {
            f32 len = Length();
            return len > 0.0f ? Vec3{ x / len, y / len, z / len } : Vec3{ 0.0f };
        }

        static constexpr Vec3 Zero()    { return { 0, 0, 0 }; }
        static constexpr Vec3 One()     { return { 1, 1, 1 }; }
        static constexpr Vec3 Up()      { return { 0, 1, 0 }; }
        static constexpr Vec3 Right()   { return { 1, 0, 0 }; }
        static constexpr Vec3 Forward() { return { 0, 0, -1 }; }
    };

    inline Vec3 Lerp(const Vec3& a, const Vec3& b, f32 t) {
        return a + (b - a) * t;
    }

} // namespace LRT::Math

