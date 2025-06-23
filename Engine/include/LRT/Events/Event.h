#pragma once

#include "LRT/Core/Types.h"
#include <functional>
#include <string>
#include <type_traits>

namespace LRT {

    enum class EventType : u32 {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class EventCategory : u32 {
        None        = 0,
        Application = 1 << 0,
        Input       = 1 << 1,
        Keyboard    = 1 << 2,
        Mouse       = 1 << 3,
        MouseButton = 1 << 4
    };

    inline EventCategory operator|(EventCategory a, EventCategory b) {
        return static_cast<EventCategory>(static_cast<u32>(a) | static_cast<u32>(b));
    }

    inline bool operator&(EventCategory a, EventCategory b) {
        return (static_cast<u32>(a) & static_cast<u32>(b)) != 0;
    }

    class Event {
    public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual EventCategory GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool Handled = false;

        bool IsInCategory(EventCategory category) const {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher {
    public:
        explicit EventDispatcher(Event& event) : m_Event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    // Concrete event types
    class WindowCloseEvent : public Event {
    public:
        EventType GetEventType() const override { return EventType::WindowClose; }
        const char* GetName() const override { return "WindowClose"; }
        EventCategory GetCategoryFlags() const override { return EventCategory::Application; }
        static EventType GetStaticType() { return EventType::WindowClose; }
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(u32 width, u32 height) : m_Width(width), m_Height(height) {}

        u32 GetWidth() const { return m_Width; }
        u32 GetHeight() const { return m_Height; }

        EventType GetEventType() const override { return EventType::WindowResize; }
        const char* GetName() const override { return "WindowResize"; }
        EventCategory GetCategoryFlags() const override { return EventCategory::Application; }
        static EventType GetStaticType() { return EventType::WindowResize; }

        std::string ToString() const override {
            return std::format("WindowResize: {}x{}", m_Width, m_Height);
        }

    private:
        u32 m_Width, m_Height;
    };

    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(i32 keyCode, bool isRepeat = false)
            : m_KeyCode(keyCode), m_IsRepeat(isRepeat) {}

        i32 GetKeyCode() const { return m_KeyCode; }
        bool IsRepeat() const { return m_IsRepeat; }

        EventType GetEventType() const override { return EventType::KeyPressed; }
        const char* GetName() const override { return "KeyPressed"; }
        EventCategory GetCategoryFlags() const override { return EventCategory::Keyboard | EventCategory::Input; }
        static EventType GetStaticType() { return EventType::KeyPressed; }

    private:
        i32 m_KeyCode;
        bool m_IsRepeat;
    };

    class KeyReleasedEvent : public Event {
    public:
        explicit KeyReleasedEvent(i32 keyCode) : m_KeyCode(keyCode) {}
        i32 GetKeyCode() const { return m_KeyCode; }

        EventType GetEventType() const override { return EventType::KeyReleased; }
        const char* GetName() const override { return "KeyReleased"; }
        EventCategory GetCategoryFlags() const override { return EventCategory::Keyboard | EventCategory::Input; }
        static EventType GetStaticType() { return EventType::KeyReleased; }

    private:
        i32 m_KeyCode;
    };

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(f32 x, f32 y) : m_X(x), m_Y(y) {}
        f32 GetX() const { return m_X; }
        f32 GetY() const { return m_Y; }

        EventType GetEventType() const override { return EventType::MouseMoved; }
        const char* GetName() const override { return "MouseMoved"; }
        EventCategory GetCategoryFlags() const override { return EventCategory::Mouse | EventCategory::Input; }
        static EventType GetStaticType() { return EventType::MouseMoved; }

    private:
        f32 m_X, m_Y;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(f32 xOffset, f32 yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        f32 GetXOffset() const { return m_XOffset; }
        f32 GetYOffset() const { return m_YOffset; }

        EventType GetEventType() const override { return EventType::MouseScrolled; }
        const char* GetName() const override { return "MouseScrolled"; }
        EventCategory GetCategoryFlags() const override { return EventCategory::Mouse | EventCategory::Input; }
        static EventType GetStaticType() { return EventType::MouseScrolled; }

    private:
        f32 m_XOffset, m_YOffset;
    };

    class MouseButtonPressedEvent : public Event {
    public:
        explicit MouseButtonPressedEvent(i32 button) : m_Button(button) {}
        i32 GetButton() const { return m_Button; }

        EventType GetEventType() const override { return EventType::MouseButtonPressed; }
        const char* GetName() const override { return "MouseButtonPressed"; }
        EventCategory GetCategoryFlags() const override { return EventCategory::MouseButton | EventCategory::Input; }
        static EventType GetStaticType() { return EventType::MouseButtonPressed; }

    private:
        i32 m_Button;
    };

} // namespace LRT
