#include "ComponentInspector.h"
#include "LRT/Core/Logger.h"
#include "LRT/Math/Transform.h"

namespace LRTEditor {

    void ComponentInspector::SetContext(const LRT::Shared<LRT::ECS::Scene>& scene,
                                        LRT::EntityID entity) {
        m_Scene = scene;
        m_Entity = entity;
    }

    void ComponentInspector::OnImGuiRender() {
        // ImGui::Begin("Inspector");

        if (m_Entity == LRT::NullEntity || !m_Scene) {
            // ImGui::Text("No entity selected");
            // ImGui::End();
            return;
        }

        // ImGui::Text("Entity %llu", m_Entity);
        // ImGui::Separator();

        DrawTransformComponent();
        DrawAddComponentButton();

        // ImGui::End();
    }

    void ComponentInspector::DrawTransformComponent() {
        // if (!m_Scene->HasComponent<LRT::Math::Transform>(m_Entity)) return;

        // ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed;
        // if (ImGui::TreeNodeEx("Transform", flags)) {
        //     auto& transform = m_Scene->GetComponent<LRT::Math::Transform>(m_Entity);
        //
        //     ImGui::DragFloat3("Position", &transform.Position.x, 0.1f);
        //
        //     // Display rotation in degrees
        //     LRT::Math::Vec3 rotDeg = {
        //         transform.Rotation.x * 57.2957795f,
        //         transform.Rotation.y * 57.2957795f,
        //         transform.Rotation.z * 57.2957795f
        //     };
        //     if (ImGui::DragFloat3("Rotation", &rotDeg.x, 1.0f)) {
        //         transform.Rotation = {
        //             rotDeg.x * 0.0174532925f,
        //             rotDeg.y * 0.0174532925f,
        //             rotDeg.z * 0.0174532925f
        //         };
        //     }
        //
        //     ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f, 0.01f, 100.0f);
        //     ImGui::TreePop();
        // }
    }

    void ComponentInspector::DrawAddComponentButton() {
        // ImGui::Spacing();
        // float width = ImGui::GetContentRegionAvail().x;
        // if (ImGui::Button("Add Component", { width, 0 })) {
        //     ImGui::OpenPopup("AddComponent");
        // }
        //
        // if (ImGui::BeginPopup("AddComponent")) {
        //     if (ImGui::MenuItem("Transform")) {
        //         m_Scene->AddComponent<LRT::Math::Transform>(m_Entity, {});
        //     }
        //     // Add more component types here
        //     ImGui::EndPopup();
        // }
    }

} // namespace LRTEditor
