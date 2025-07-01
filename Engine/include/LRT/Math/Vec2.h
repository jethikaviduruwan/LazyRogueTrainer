#pragma once

#include "LRT/Core/Types.h"
#include <cmath>

namespace LRT::Math {

    struct Vec2 {
        f32 x = 0.0f;
        f32 y = 0.0f;

        constexpr Vec2() = default;
        constexpr Vec2(f32 x, f32 y) : x(x), y(y) {}
        constexpr explicit Vec2(f32 scalar) : x(scalar), y(scalar) {}

        constexpr Vec2 operator+(const Vec2& rhs) const { return { x + rhs.x, y + rhs.y }; }
        constexpr Vec2 operator-(const Vec2& rhs) const { return { x - rhs.x, y - rhs.y }; }
        constexpr Vec2 operator*(f32 scalar) const { return { x * scalar, y * scalar }; }
        constexpr Vec2 operator/(f32 scalar) const { return { x / scalar, y / scalar }; }

        Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
        Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
        Vec2& operator*=(f32 scalar) { x *= scalar; y *= scalar; return *this; }

        constexpr f32 Dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }
        f32 Length() const { return std::sqrt(x * x + y * y); }
        constexpr f32 LengthSquared() const { return x * x + y * y; }

        Vec2 Normalized() const {
            f32 len = Length();
            return len > 0.0f ? Vec2{ x / len, y / len } : Vec2{ 0.0f, 0.0f };
        }

        static constexpr Vec2 Zero() { return { 0.0f, 0.0f }; }
        static constexpr Vec2 One() { return { 1.0f, 1.0f }; }
        static constexpr Vec2 Up() { return { 0.0f, 1.0f }; }
        static constexpr Vec2 Right() { return { 1.0f, 0.0f }; }
    };

} // namespace LRT::Math
