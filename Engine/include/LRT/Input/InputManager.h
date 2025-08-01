#pragma once

#include "LRT/Core/Types.h"
#include "LRT/Math/Vec2.h"
#include <array>

namespace LRT {

    namespace KeyCode {
        constexpr i32 Space = 32;
        constexpr i32 Escape = 256;
        constexpr i32 Enter = 257;
        constexpr i32 Tab = 258;
        constexpr i32 Right = 262;
        constexpr i32 Left = 263;
        constexpr i32 Down = 264;
        constexpr i32 Up = 265;
        constexpr i32 A = 65, B = 66, C = 67, D = 68;
        constexpr i32 W = 87, S = 83;
        constexpr i32 Q = 81, E = 69;
        constexpr i32 LeftShift = 340;
        constexpr i32 LeftControl = 341;
    }

    namespace MouseButton {
        constexpr i32 Left = 0;
        constexpr i32 Right = 1;
        constexpr i32 Middle = 2;
    }

    class InputManager {
    public:
        static InputManager& Get() {
            static InputManager instance;
            return instance;
        }

        void Update();

        // Keyboard
        bool IsKeyDown(i32 keyCode) const;
        bool IsKeyUp(i32 keyCode) const;
        bool WasKeyPressed(i32 keyCode) const;  // just this frame
        bool WasKeyReleased(i32 keyCode) const;

        void SetKeyState(i32 keyCode, bool pressed);

        // Mouse
        bool IsMouseButtonDown(i32 button) const;
        bool WasMouseButtonPressed(i32 button) const;
        void SetMouseButtonState(i32 button, bool pressed);

        void SetMousePosition(f32 x, f32 y);
        Math::Vec2 GetMousePosition() const { return m_MousePos; }
        Math::Vec2 GetMouseDelta() const { return m_MouseDelta; }

        void SetScrollOffset(f32 x, f32 y);
        Math::Vec2 GetScrollOffset() const { return m_ScrollOffset; }

    private:
        InputManager() = default;

        static constexpr u32 MAX_KEYS = 512;
        static constexpr u32 MAX_BUTTONS = 8;

        std::array<bool, MAX_KEYS> m_Keys{};
        std::array<bool, MAX_KEYS> m_PrevKeys{};
        std::array<bool, MAX_BUTTONS> m_MouseButtons{};
        std::array<bool, MAX_BUTTONS> m_PrevMouseButtons{};

        Math::Vec2 m_MousePos{0.0f, 0.0f};
        Math::Vec2 m_PrevMousePos{0.0f, 0.0f};
        Math::Vec2 m_MouseDelta{0.0f, 0.0f};
        Math::Vec2 m_ScrollOffset{0.0f, 0.0f};
    };

} // namespace LRT
