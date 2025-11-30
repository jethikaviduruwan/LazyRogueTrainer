# LazyRogueTrainer

**A Modern C++ Game Engine Focused on Performance and Clean Architecture**

LazyRogueTrainer is a from-scratch game engine written in modern C++ (C++20), designed to explore low-level systems programming, engine architecture, and performance-oriented design. The project focuses on memory efficiency, modularity, and real-time rendering, while providing an editor-driven workflow.

## Key Features

### Modular Engine Architecture
- Clear separation between Core, Rendering, ECS, and Editor layers
- Scalable and maintainable design with minimal coupling

### Entity Component System (ECS)
- Cache-friendly packed component arrays
- Efficient entity iteration and component management
- System-based update loop with automatic entity matching

### Custom Memory Management
- **Linear Allocator** — fast bump allocation for per-frame temporary data
- **Pool Allocator** — fixed-size block allocation with free-list recycling
- **Memory Tracker** — debug allocation tracking and leak detection

### Rendering Engine
- OpenGL-based real-time 2D renderer with batched draw calls
- Abstraction layers for shaders, vertex/index buffers, textures, framebuffers, and render commands
- Orthographic and perspective camera support

### Event & Input System
- Type-safe event dispatching with compile-time polymorphism
- Publish/subscribe event bus with handler IDs
- Keyboard and mouse input tracking with per-frame delta

### Editor Integration
- ImGui-powered editor layer
- Scene hierarchy panel with entity management
- Component inspector with transform editing
- Viewport rendering through framebuffer

### Modern C++ Practices
- RAII-based resource management throughout
- Smart pointers and move semantics
- Const-correctness and value semantics
- `constexpr` math operations where possible

## Technical Focus Areas

- Low-level C++ systems programming
- Performance optimization and cache-friendly data layouts
- Memory safety and lifetime management
- Engine-style architecture used in real-world applications

## Tech Stack

| Component    | Technology          |
|-------------|---------------------|
| Language    | C++20               |
| Graphics    | OpenGL              |
| Windowing   | GLFW                |
| UI / Editor | Dear ImGui          |
| Build System| CMake (3.20+)       |
| Platform    | Windows / Linux     |

## Project Structure

```
LazyRogueTrainer/
├── CMakeLists.txt
├── Engine/
│   ├── CMakeLists.txt
│   ├── include/LRT/
│   │   ├── Core/          # Application, Window, Logger, Timer, LayerStack
│   │   ├── ECS/           # EntityManager, ComponentRegistry, SystemManager, Scene
│   │   ├── Events/        # Event types, EventBus
│   │   ├── Input/         # InputManager, key/mouse codes
│   │   ├── Math/          # Vec2, Vec3, Vec4, Mat4, Transform
│   │   ├── Memory/        # LinearAllocator, PoolAllocator, MemoryTracker
│   │   └── Renderer/      # Shader, Buffers, Texture, Framebuffer, Renderer2D, Camera
│   └── src/
│       └── ...            # Corresponding implementations
├── Editor/
│   ├── CMakeLists.txt
│   ├── include/           # EditorLayer, SceneHierarchy, ComponentInspector
│   └── src/
└── .gitignore
```

## Building

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Build Options

| Option            | Default | Description                  |
|-------------------|---------|------------------------------|
| LRT_BUILD_EDITOR  | ON      | Build the editor application |
| LRT_BUILD_TESTS   | OFF     | Build unit tests             |

## Roadmap

- [x] Core engine framework (Application, Window, Layers)
- [x] Event system with type-safe dispatch
- [x] Input management
- [x] Custom memory allocators
- [x] Math library (vectors, matrices, transforms)
- [x] Entity Component System
- [x] 2D batch renderer scaffolding
- [x] Editor with ImGui panels
- [ ] Scene serialization (JSON/binary)
- [ ] Audio system integration
- [ ] Physics (collision detection, rigid bodies)
- [ ] Scripting layer
- [ ] 3D renderer with PBR materials

## License

This project is for educational and portfolio purposes.
