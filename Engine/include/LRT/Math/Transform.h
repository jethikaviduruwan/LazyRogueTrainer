#pragma once

#include "LRT/Math/Vec3.h"
#include "LRT/Math/Mat4.h"

namespace LRT::Math {

    struct Transform {
        Vec3 Position{ 0.0f, 0.0f, 0.0f };
        Vec3 Rotation{ 0.0f, 0.0f, 0.0f };  // Euler angles in radians
        Vec3 Scale{ 1.0f, 1.0f, 1.0f };

        Mat4 GetMatrix() const {
            return Mat4::Translate(Position)
                 * Mat4::RotateZ(Rotation.z)
                 * Mat4::RotateY(Rotation.y)
                 * Mat4::RotateX(Rotation.x)
                 * Mat4::Scale(Scale);
        }
    };

} // namespace LRT::Math
