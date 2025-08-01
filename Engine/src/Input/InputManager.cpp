#include "LRT/Input/InputManager.h"

namespace LRT {

    void InputManager::Update() {
        m_PrevKeys = m_Keys;
        m_PrevMouseButtons = m_MouseButtons;
        m_MouseDelta = { m_MousePos.x - m_PrevMousePos.x, m_MousePos.y - m_PrevMousePos.y };
        m_PrevMousePos = m_MousePos;
        m_ScrollOffset = { 0.0f, 0.0f };
    }

    bool InputManager::IsKeyDown(i32 keyCode) const {
        if (keyCode < 0 || keyCode >= static_cast<i32>(MAX_KEYS)) return false;
        return m_Keys[keyCode];
    }

    bool InputManager::IsKeyUp(i32 keyCode) const {
        return !IsKeyDown(keyCode);
    }

    bool InputManager::WasKeyPressed(i32 keyCode) const {
        if (keyCode < 0 || keyCode >= static_cast<i32>(MAX_KEYS)) return false;
        return m_Keys[keyCode] && !m_PrevKeys[keyCode];
    }

    bool InputManager::WasKeyReleased(i32 keyCode) const {
        if (keyCode < 0 || keyCode >= static_cast<i32>(MAX_KEYS)) return false;
        return !m_Keys[keyCode] && m_PrevKeys[keyCode];
    }

    void InputManager::SetKeyState(i32 keyCode, bool pressed) {
        if (keyCode >= 0 && keyCode < static_cast<i32>(MAX_KEYS)) {
            m_Keys[keyCode] = pressed;
        }
    }

    bool InputManager::IsMouseButtonDown(i32 button) const {
        if (button < 0 || button >= static_cast<i32>(MAX_BUTTONS)) return false;
        return m_MouseButtons[button];
    }

    bool InputManager::WasMouseButtonPressed(i32 button) const {
        if (button < 0 || button >= static_cast<i32>(MAX_BUTTONS)) return false;
        return m_MouseButtons[button] && !m_PrevMouseButtons[button];
    }

    void InputManager::SetMouseButtonState(i32 button, bool pressed) {
        if (button >= 0 && button < static_cast<i32>(MAX_BUTTONS)) {
            m_MouseButtons[button] = pressed;
        }
    }

    void InputManager::SetMousePosition(f32 x, f32 y) {
        m_MousePos = { x, y };
    }

    void InputManager::SetScrollOffset(f32 x, f32 y) {
        m_ScrollOffset = { x, y };
    }

} // namespace LRT
