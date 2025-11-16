#pragma once

#include "LRT/Core/Types.h"
#include "LRT/ECS/EntityManager.h"
#include <set>
#include <unordered_map>
#include <typeindex>

namespace LRT::ECS {

    class System {
    public:
        virtual ~System() = default;
        virtual void Update(f32 deltaTime) = 0;

        std::set<EntityID> Entities;
    };

    class SystemManager {
    public:
        template<typename T, typename... Args>
        Shared<T> RegisterSystem(Args&&... args) {
            auto typeIdx = std::type_index(typeid(T));
            LRT_ASSERT_MSG(m_Systems.find(typeIdx) == m_Systems.end(),
                           "System already registered");
            auto system = MakeShared<T>(std::forward<Args>(args)...);
            m_Systems[typeIdx] = system;
            return system;
        }

        template<typename T>
        void SetSignature(ComponentMask signature) {
            auto typeIdx = std::type_index(typeid(T));
            m_Signatures[typeIdx] = signature;
        }

        template<typename T>
        Shared<T> GetSystem() {
            auto typeIdx = std::type_index(typeid(T));
            auto it = m_Systems.find(typeIdx);
            LRT_ASSERT_MSG(it != m_Systems.end(), "System not registered");
            return std::static_pointer_cast<T>(it->second);
        }

        void EntityDestroyed(EntityID entity) {
            for (auto& [type, system] : m_Systems) {
                system->Entities.erase(entity);
            }
        }

        void EntitySignatureChanged(EntityID entity, ComponentMask entityMask) {
            for (auto& [type, system] : m_Systems) {
                auto it = m_Signatures.find(type);
                if (it == m_Signatures.end()) continue;

                const ComponentMask& systemMask = it->second;
                if ((entityMask & systemMask) == systemMask) {
                    system->Entities.insert(entity);
                } else {
                    system->Entities.erase(entity);
                }
            }
        }

        void UpdateAll(f32 deltaTime) {
            for (auto& [type, system] : m_Systems) {
                system->Update(deltaTime);
            }
        }

    private:
        std::unordered_map<std::type_index, Shared<System>> m_Systems;
        std::unordered_map<std::type_index, ComponentMask> m_Signatures;
    };

} // namespace LRT::ECS

