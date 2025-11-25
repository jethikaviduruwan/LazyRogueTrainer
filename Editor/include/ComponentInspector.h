#pragma once

#include "LRT/Core/Types.h"
#include "LRT/ECS/Scene.h"

namespace LRTEditor {

    class ComponentInspector {
    public:
        ComponentInspector() = default;

        void SetContext(const LRT::Shared<LRT::ECS::Scene>& scene, LRT::EntityID entity);
        void OnImGuiRender();

    private:
        void DrawTransformComponent();
        void DrawAddComponentButton();

        LRT::Shared<LRT::ECS::Scene> m_Scene;
        LRT::EntityID m_Entity = LRT::NullEntity;
    };

} // namespace LRTEditor
