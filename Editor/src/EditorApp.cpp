#include "LRT/Core/Application.h"
#include "EditorLayer.h"

class LRTEditorApp : public LRT::Application {
public:
    LRTEditorApp()
        : Application({ "LazyRogueTrainer Editor", 1600, 900 }) {
        PushLayer(new LRTEditor::EditorLayer());
    }
};

LRT::Application* LRT::CreateApplication() {
    return new LRTEditorApp();
}

int main(int argc, char** argv) {
    auto app = LRT::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
