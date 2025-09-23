#include "LRT/ECS/Scene.h"
#include "LRT/Core/Logger.h"

namespace LRT::ECS {

    Scene::Scene(const std::string& name)
        : m_Name(name) {
        LRT_INFO("Scene '{}' created", m_Name);
    }

    EntityID Scene::CreateEntity() {
        EntityID id = m_EntityManager.CreateEntity();
        LRT_TRACE("Entity {} created in scene '{}'", id, m_Name);
        return id;
    }

    void Scene::DestroyEntity(EntityID entity) {
        m_SystemManager.EntityDestroyed(entity);
        m_ComponentRegistry.EntityDestroyed(entity);
        m_EntityManager.DestroyEntity(entity);
        LRT_TRACE("Entity {} destroyed in scene '{}'", entity, m_Name);
    }

    void Scene::Update(f32 deltaTime) {
        m_SystemManager.UpdateAll(deltaTime);
    }

} // namespace LRT::ECS
