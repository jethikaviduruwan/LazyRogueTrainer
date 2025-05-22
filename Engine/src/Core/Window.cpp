#include "LRT/Core/Window.h"
#include "LRT/Core/Logger.h"

namespace LRT {

    Window::Window(const WindowProps& props) {
        Init(props);
    }

    Window::~Window() {
        Shutdown();
    }

    void Window::Init(const WindowProps& props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.VSync = props.VSync;

        LRT_INFO("Creating window '{}' ({}x{})", m_Data.Title, m_Data.Width, m_Data.Height);

        // GLFW initialization would go here
        // glfwInit();
        // m_Window = glfwCreateWindow(...);
    }

    void Window::Shutdown() {
        LRT_INFO("Destroying window '{}'", m_Data.Title);
        // glfwDestroyWindow(static_cast<GLFWwindow*>(m_Window));
        // glfwTerminate();
    }

    void Window::OnUpdate() {
        // glfwPollEvents();
        // glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window));
    }

    void Window::SetVSync(bool enabled) {
        m_Data.VSync = enabled;
        // glfwSwapInterval(enabled ? 1 : 0);
    }

    bool Window::ShouldClose() const {
        // return glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Window));
        return false;
    }

    Unique<Window> Window::Create(const WindowProps& props) {
        return MakeUnique<Window>(props);
    }

} // namespace LRT
