#pragma once

#include "LRT/Core/Types.h"
#include "LRT/ECS/EntityManager.h"
#include "LRT/ECS/ComponentRegistry.h"
#include "LRT/ECS/SystemManager.h"
#include <string>

namespace LRT::ECS {

    class Scene {
    public:
        explicit Scene(const std::string& name = "Untitled");
        ~Scene() = default;

        // Entity operations
        EntityID CreateEntity();
        void DestroyEntity(EntityID entity);

        // Component operations
        template<typename T>
        void RegisterComponent() {
            m_ComponentRegistry.RegisterComponent<T>();
        }

        template<typename T>
        void AddComponent(EntityID entity, T component) {
            m_ComponentRegistry.GetComponentArray<T>()->Insert(entity, std::move(component));

            auto mask = m_EntityManager.GetComponentMask(entity);
            mask.set(m_ComponentRegistry.GetComponentTypeID<T>());
            m_EntityManager.SetComponentMask(entity, mask);
            m_SystemManager.EntitySignatureChanged(entity, mask);
        }

        template<typename T>
        void RemoveComponent(EntityID entity) {
            m_ComponentRegistry.GetComponentArray<T>()->Remove(entity);

            auto mask = m_EntityManager.GetComponentMask(entity);
            mask.reset(m_ComponentRegistry.GetComponentTypeID<T>());
            m_EntityManager.SetComponentMask(entity, mask);
            m_SystemManager.EntitySignatureChanged(entity, mask);
        }

        template<typename T>
        T& GetComponent(EntityID entity) {
            return m_ComponentRegistry.GetComponentArray<T>()->Get(entity);
        }

        template<typename T>
        bool HasComponent(EntityID entity) {
            return m_ComponentRegistry.GetComponentArray<T>()->HasComponent(entity);
        }

        // System operations
        template<typename T, typename... Args>
        Shared<T> RegisterSystem(Args&&... args) {
            return m_SystemManager.RegisterSystem<T>(std::forward<Args>(args)...);
        }

        template<typename T>
        void SetSystemSignature(ComponentMask mask) {
            m_SystemManager.SetSignature<T>(mask);
        }

        void Update(f32 deltaTime);

        const std::string& GetName() const { return m_Name; }
        u32 GetEntityCount() const { return m_EntityManager.GetLivingEntityCount(); }

    private:
        std::string m_Name;
        EntityManager m_EntityManager;
        ComponentRegistry m_ComponentRegistry;
        SystemManager m_SystemManager;
    };

} // namespace LRT::ECS
