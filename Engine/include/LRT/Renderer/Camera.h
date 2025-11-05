#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Math/Mat4.h"
#include "LRT/Math/Vec3.h"

namespace LRT::Renderer {

    class Camera {
    public:
        Camera() = default;
        virtual ~Camera() = default;

        const Math::Mat4& GetProjection() const { return m_Projection; }

    protected:
        Math::Mat4 m_Projection = Math::Mat4::Identity();
    };

    class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top);

        void SetProjection(f32 left, f32 right, f32 bottom, f32 top);

        const Math::Vec3& GetPosition() const { return m_Position; }
        void SetPosition(const Math::Vec3& position) { m_Position = position; RecalculateView(); }

        f32 GetRotation() const { return m_Rotation; }
        void SetRotation(f32 rotation) { m_Rotation = rotation; RecalculateView(); }

        const Math::Mat4& GetViewMatrix() const { return m_ViewMatrix; }
        Math::Mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

    private:
        void RecalculateView();

        Math::Vec3 m_Position{ 0.0f, 0.0f, 0.0f };
        f32 m_Rotation = 0.0f;
        Math::Mat4 m_ViewMatrix = Math::Mat4::Identity();
    };

    class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(f32 fovDegrees, f32 aspect, f32 nearClip, f32 farClip);

        void SetProjection(f32 fovDegrees, f32 aspect, f32 nearClip, f32 farClip);

        const Math::Vec3& GetPosition() const { return m_Position; }
        void SetPosition(const Math::Vec3& pos) { m_Position = pos; RecalculateView(); }

        const Math::Vec3& GetTarget() const { return m_Target; }
        void SetTarget(const Math::Vec3& target) { m_Target = target; RecalculateView(); }

        const Math::Mat4& GetViewMatrix() const { return m_ViewMatrix; }
        Math::Mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

    private:
        void RecalculateView();

        Math::Vec3 m_Position{ 0.0f, 0.0f, 5.0f };
        Math::Vec3 m_Target{ 0.0f, 0.0f, 0.0f };
        Math::Vec3 m_Up{ 0.0f, 1.0f, 0.0f };
        Math::Mat4 m_ViewMatrix = Math::Mat4::Identity();
    };

} // namespace LRT::Renderer
