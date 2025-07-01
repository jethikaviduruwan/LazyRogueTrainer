#pragma once

#include "LRT/Events/Event.h"
#include <vector>
#include <functional>
#include <unordered_map>

namespace LRT {

    class EventBus {
    public:
        using HandlerFn = std::function<void(Event&)>;

        static EventBus& Get() {
            static EventBus instance;
            return instance;
        }

        u32 Subscribe(EventType type, HandlerFn handler) {
            u32 id = m_NextID++;
            m_Handlers[type].push_back({ id, std::move(handler) });
            return id;
        }

        void Unsubscribe(EventType type, u32 handlerID) {
            auto it = m_Handlers.find(type);
            if (it == m_Handlers.end()) return;
            auto& vec = it->second;
            vec.erase(
                std::remove_if(vec.begin(), vec.end(),
                    [handlerID](const HandlerEntry& e) { return e.ID == handlerID; }),
                vec.end()
            );
        }

        void Publish(Event& event) {
            auto it = m_Handlers.find(event.GetEventType());
            if (it == m_Handlers.end()) return;
            for (auto& entry : it->second) {
                if (event.Handled) break;
                entry.Handler(event);
            }
        }

        void Clear() { m_Handlers.clear(); }

    private:
        EventBus() = default;

        struct HandlerEntry {
            u32 ID;
            HandlerFn Handler;
        };

        std::unordered_map<EventType, std::vector<HandlerEntry>> m_Handlers;
        u32 m_NextID = 1;
    };

} // namespace LRT
