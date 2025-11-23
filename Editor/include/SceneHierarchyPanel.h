#pragma once

#include "LRT/Core/Types.h"
#include "LRT/ECS/Scene.h"

namespace LRTEditor {

    class SceneHierarchyPanel {
    public:
        SceneHierarchyPanel() = default;

        void SetScene(const LRT::Shared<LRT::ECS::Scene>& scene);
        void OnImGuiRender();

        LRT::EntityID GetSelectedEntity() const { return m_SelectedEntity; }
        void SetSelectedEntity(LRT::EntityID entity) { m_SelectedEntity = entity; }

    private:
        void DrawEntityNode(LRT::EntityID entity);

        LRT::Shared<LRT::ECS::Scene> m_Scene;
        LRT::EntityID m_SelectedEntity = LRT::NullEntity;
    };

} // namespace LRTEditor
