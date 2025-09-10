#pragma once

#include "LRT/Core/Types.h"
#include <vector>
#include <queue>
#include <bitset>

namespace LRT::ECS {

    constexpr u32 MAX_COMPONENTS = 64;
    using ComponentMask = std::bitset<MAX_COMPONENTS>;

    class EntityManager {
    public:
        EntityManager();

        EntityID CreateEntity();
        void DestroyEntity(EntityID id);
        bool IsAlive(EntityID id) const;

        void SetComponentMask(EntityID id, ComponentMask mask);
        ComponentMask GetComponentMask(EntityID id) const;

        [[nodiscard]] u32 GetLivingEntityCount() const { return m_LivingCount; }
        [[nodiscard]] u32 GetCapacity() const { return static_cast<u32>(m_Masks.size()); }

        const std::vector<EntityID>& GetAllEntities() const { return m_ActiveEntities; }

    private:
        std::queue<EntityID> m_Available;
        std::vector<ComponentMask> m_Masks;
        std::vector<bool> m_Alive;
        std::vector<EntityID> m_ActiveEntities;
        EntityID m_NextID = 1;
        u32 m_LivingCount = 0;
    };

} // namespace LRT::ECS
