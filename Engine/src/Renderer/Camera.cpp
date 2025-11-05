#include "LRT/Renderer/Camera.h"
#include <cmath>

namespace LRT::Renderer {

    // --- OrthographicCamera ---

    OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top) {
        m_Projection = Math::Mat4::Ortho(left, right, bottom, top, -1.0f, 1.0f);
        RecalculateView();
    }

    void OrthographicCamera::SetProjection(f32 left, f32 right, f32 bottom, f32 top) {
        m_Projection = Math::Mat4::Ortho(left, right, bottom, top, -1.0f, 1.0f);
    }

    void OrthographicCamera::RecalculateView() {
        auto transform = Math::Mat4::Translate(m_Position) * Math::Mat4::RotateZ(m_Rotation);

        // Simple inverse for orthographic: negate translation, transpose rotation
        // For simplicity, reconstruct with LookAt-style inverse
        f32 cosR = std::cos(-m_Rotation);
        f32 sinR = std::sin(-m_Rotation);

        m_ViewMatrix = Math::Mat4::Identity();
        m_ViewMatrix(0, 0) = cosR;
        m_ViewMatrix(0, 1) = sinR;
        m_ViewMatrix(1, 0) = -sinR;
        m_ViewMatrix(1, 1) = cosR;
        m_ViewMatrix(0, 3) = -m_Position.x * cosR - m_Position.y * sinR;
        m_ViewMatrix(1, 3) = m_Position.x * sinR - m_Position.y * cosR;
        m_ViewMatrix(2, 3) = -m_Position.z;
    }

    // --- PerspectiveCamera ---

    PerspectiveCamera::PerspectiveCamera(f32 fovDegrees, f32 aspect, f32 nearClip, f32 farClip) {
        constexpr f32 DEG_TO_RAD = 3.14159265358979f / 180.0f;
        m_Projection = Math::Mat4::Perspective(fovDegrees * DEG_TO_RAD, aspect, nearClip, farClip);
        RecalculateView();
    }

    void PerspectiveCamera::SetProjection(f32 fovDegrees, f32 aspect, f32 nearClip, f32 farClip) {
        constexpr f32 DEG_TO_RAD = 3.14159265358979f / 180.0f;
        m_Projection = Math::Mat4::Perspective(fovDegrees * DEG_TO_RAD, aspect, nearClip, farClip);
    }

    void PerspectiveCamera::RecalculateView() {
        m_ViewMatrix = Math::Mat4::LookAt(m_Position, m_Target, m_Up);
    }

} // namespace LRT::Renderer
