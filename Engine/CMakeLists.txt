add_library(LRTEngine STATIC
    # Core
    src/Core/Application.cpp
    src/Core/Window.cpp
    src/Core/Logger.cpp
    src/Core/LayerStack.cpp
    src/Core/Timer.cpp

    # Events
    src/Events/EventBus.cpp

    # Input
    src/Input/InputManager.cpp

    # Memory
    src/Memory/LinearAllocator.cpp
    src/Memory/PoolAllocator.cpp
    src/Memory/MemoryTracker.cpp

    # ECS
    src/ECS/EntityManager.cpp
    src/ECS/ComponentRegistry.cpp
    src/ECS/SystemManager.cpp
    src/ECS/Scene.cpp

    # Renderer
    src/Renderer/RenderContext.cpp
    src/Renderer/Shader.cpp
    src/Renderer/VertexBuffer.cpp
    src/Renderer/IndexBuffer.cpp
    src/Renderer/VertexArray.cpp
    src/Renderer/Texture2D.cpp
    src/Renderer/Framebuffer.cpp
    src/Renderer/Renderer2D.cpp
    src/Renderer/RenderCommand.cpp
    src/Renderer/Camera.cpp

    # Math
    src/Math/Vec2.cpp
    src/Math/Vec3.cpp
    src/Math/Vec4.cpp
    src/Math/Mat4.cpp
    src/Math/Transform.cpp
)

target_include_directories(LRTEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(LRTEngine PUBLIC cxx_std_20)

# Platform detection
if(WIN32)
    target_compile_definitions(LRTEngine PUBLIC LRT_PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(LRTEngine PUBLIC LRT_PLATFORM_LINUX)
endif()

target_compile_definitions(LRTEngine PUBLIC
    LRT_ENGINE_VERSION="${PROJECT_VERSION}"
    $<$<CONFIG:Debug>:LRT_DEBUG>
    $<$<CONFIG:Release>:LRT_RELEASE>
)
