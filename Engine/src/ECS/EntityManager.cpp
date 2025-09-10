#include "LRT/ECS/EntityManager.h"
#include "LRT/Core/Logger.h"
#include <algorithm>

namespace LRT::ECS {

    EntityManager::EntityManager() {
        m_Masks.reserve(1024);
        m_Alive.reserve(1024);
        m_ActiveEntities.reserve(1024);
    }

    EntityID EntityManager::CreateEntity() {
        EntityID id;
        if (!m_Available.empty()) {
            id = m_Available.front();
            m_Available.pop();
            m_Alive[id] = true;
        } else {
            id = m_NextID++;
            if (id >= m_Masks.size()) {
                m_Masks.resize(id + 1);
                m_Alive.resize(id + 1, false);
            }
            m_Alive[id] = true;
        }
        m_Masks[id].reset();
        m_ActiveEntities.push_back(id);
        m_LivingCount++;
        return id;
    }

    void EntityManager::DestroyEntity(EntityID id) {
        LRT_ASSERT_MSG(id < m_Alive.size() && m_Alive[id], "Destroying invalid entity");
        m_Alive[id] = false;
        m_Masks[id].reset();
        m_Available.push(id);
        m_LivingCount--;

        auto it = std::find(m_ActiveEntities.begin(), m_ActiveEntities.end(), id);
        if (it != m_ActiveEntities.end()) {
            *it = m_ActiveEntities.back();
            m_ActiveEntities.pop_back();
        }
    }

    bool EntityManager::IsAlive(EntityID id) const {
        return id < m_Alive.size() && m_Alive[id];
    }

    void EntityManager::SetComponentMask(EntityID id, ComponentMask mask) {
        LRT_ASSERT_MSG(id < m_Masks.size(), "Invalid entity ID for component mask");
        m_Masks[id] = mask;
    }

    ComponentMask EntityManager::GetComponentMask(EntityID id) const {
        LRT_ASSERT_MSG(id < m_Masks.size(), "Invalid entity ID for component mask");
        return m_Masks[id];
    }

} // namespace LRT::ECS
