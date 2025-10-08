#pragma once

#include "LRT/Core/Types.h"
#include <string>
#include <vector>

namespace LRT {

    class Layer {
    public:
        explicit Layer(const std::string& name = "Layer")
            : m_DebugName(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(f32 deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}

        const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };

    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        auto begin() { return m_Layers.begin(); }
        auto end() { return m_Layers.end(); }
        auto rbegin() { return m_Layers.rbegin(); }
        auto rend() { return m_Layers.rend(); }

        [[nodiscard]] u32 Size() const { return static_cast<u32>(m_Layers.size()); }

    private:
        std::vector<Layer*> m_Layers;
        u32 m_LayerInsertIndex = 0;
    };

} // namespace LRT

