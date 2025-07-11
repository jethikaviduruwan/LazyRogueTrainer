#pragma once

#include "LRT/Core/Types.h"

namespace LRT::Math {

    struct Vec4 {
        f32 x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

        constexpr Vec4() = default;
        constexpr Vec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}

        constexpr Vec4 operator+(const Vec4& rhs) const { return { x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w }; }
        constexpr Vec4 operator*(f32 s) const { return { x*s, y*s, z*s, w*s }; }

        constexpr f32 Dot(const Vec4& rhs) const {
            return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
        }
    };

} // namespace LRT::Math
