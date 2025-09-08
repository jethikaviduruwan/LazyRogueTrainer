#pragma once

#include "LRT/Core/Types.h"
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>

namespace LRT::ECS {

    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(EntityID entity) = 0;
        virtual bool HasComponent(EntityID entity) const = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
        void Insert(EntityID entity, T component) {
            LRT_ASSERT_MSG(m_EntityToIndex.find(entity) == m_EntityToIndex.end(),
                           "Component already exists on entity");
            u32 newIndex = static_cast<u32>(m_Components.size());
            m_EntityToIndex[entity] = newIndex;
            m_IndexToEntity[newIndex] = entity;
            m_Components.push_back(std::move(component));
        }

        void Remove(EntityID entity) {
            auto it = m_EntityToIndex.find(entity);
            if (it == m_EntityToIndex.end()) return;

            u32 removedIndex = it->second;
            u32 lastIndex = static_cast<u32>(m_Components.size()) - 1;

            if (removedIndex != lastIndex) {
                m_Components[removedIndex] = std::move(m_Components[lastIndex]);
                EntityID lastEntity = m_IndexToEntity[lastIndex];
                m_EntityToIndex[lastEntity] = removedIndex;
                m_IndexToEntity[removedIndex] = lastEntity;
            }

            m_Components.pop_back();
            m_EntityToIndex.erase(entity);
            m_IndexToEntity.erase(lastIndex);
        }

        T& Get(EntityID entity) {
            auto it = m_EntityToIndex.find(entity);
            LRT_ASSERT_MSG(it != m_EntityToIndex.end(), "Entity does not have component");
            return m_Components[it->second];
        }

        const T& Get(EntityID entity) const {
            auto it = m_EntityToIndex.find(entity);
            LRT_ASSERT_MSG(it != m_EntityToIndex.end(), "Entity does not have component");
            return m_Components[it->second];
        }

        bool HasComponent(EntityID entity) const override {
            return m_EntityToIndex.find(entity) != m_EntityToIndex.end();
        }

        void EntityDestroyed(EntityID entity) override {
            Remove(entity);
        }

        // Iterator support for system iteration
        auto begin() { return m_Components.begin(); }
        auto end() { return m_Components.end(); }
        u32 Size() const { return static_cast<u32>(m_Components.size()); }

    private:
        std::vector<T> m_Components;
        std::unordered_map<EntityID, u32> m_EntityToIndex;
        std::unordered_map<u32, EntityID> m_IndexToEntity;
    };

    class ComponentRegistry {
    public:
        template<typename T>
        ComponentTypeID RegisterComponent() {
            auto typeIdx = std::type_index(typeid(T));
            LRT_ASSERT_MSG(m_TypeToID.find(typeIdx) == m_TypeToID.end(),
                           "Component type already registered");
            ComponentTypeID id = m_NextTypeID++;
            m_TypeToID[typeIdx] = id;
            m_Arrays[typeIdx] = MakeShared<ComponentArray<T>>();
            return id;
        }

        template<typename T>
        ComponentTypeID GetComponentTypeID() const {
            auto it = m_TypeToID.find(std::type_index(typeid(T)));
            LRT_ASSERT_MSG(it != m_TypeToID.end(), "Component type not registered");
            return it->second;
        }

        template<typename T>
        Shared<ComponentArray<T>> GetComponentArray() {
            auto typeIdx = std::type_index(typeid(T));
            auto it = m_Arrays.find(typeIdx);
            LRT_ASSERT_MSG(it != m_Arrays.end(), "Component type not registered");
            return std::static_pointer_cast<ComponentArray<T>>(it->second);
        }

        void EntityDestroyed(EntityID entity) {
            for (auto& [type, array] : m_Arrays) {
                array->EntityDestroyed(entity);
            }
        }

    private:
        std::unordered_map<std::type_index, ComponentTypeID> m_TypeToID;
        std::unordered_map<std::type_index, Shared<IComponentArray>> m_Arrays;
        ComponentTypeID m_NextTypeID = 0;
    };

} // namespace LRT::ECS
