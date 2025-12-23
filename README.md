# LazyRogueTrainer 🎮

A Modern C++ Game Engine Focused on Performance and Clean Architecture

LazyRogueTrainer is a from-scratch game engine written in modern C++ (C++20), designed to explore low-level systems programming, engine architecture, and performance-oriented design.
The project focuses on memory efficiency, modularity, and real-time rendering, while providing an editor-driven workflow.

## 🚀 Key Features

- Modular Engine Architecture

  - Clear separation between Core, Rendering, ECS, and Editor layers

  - Scalable and maintainable design

- Entity Component System (ECS)

  - Cache-friendly data layouts

  - Efficient entity iteration and component management

- Custom Memory Management

  - Linear allocator

  - Pool allocator

  - Reduced heap allocations and improved runtime performance

- Rendering Engine

  - OpenGL-based real-time renderer

  - Abstraction layers for shaders, buffers, textures, and render commands

- Event & Input System

  - Type-safe event dispatching

  - Compile-time polymorphism with minimal runtime overhead

- Editor Integration

  - ImGui-powered editor

  - Scene hierarchy, component inspection, and live debugging tools

- Modern C++ Practices

  - RAII-based resource management

  - Smart pointers and move semantics

  - Const-correctness and value semantics

## 🧠 Technical Focus Areas

- Low-level C++ systems programming
- Performance optimization and profiling
- Memory safety and lifetime management
- Engine-style architecture used in real-world applications

## 🛠️ Tech Stack

- Language: C++20
- Graphics: OpenGL
- Windowing: GLFW
- UI / Editor: ImGui
- Build System: CMake
- Platform: Cross-platform (Windows / Linux)

## 📂 Project Structure (High Level)

```
LazyRogueTrainer/
├── Engine/
│   ├── Core/
│   ├── ECS/
│   ├── Renderer/
│   ├── Memory/
│   └── Events/
├── Editor/
├── Sandbox/
└── CMakeLists.txt
```

## 🧪 Current Status

🚧 Actively developed
- Features are continuously added and refactored with a focus on:
- Cleaner abstractions
- Better performance
- Improved developer tooling

## 🎯 Goals

- Build a production-style C++ game engine
- Deepen expertise in low-level systems and engine development
- Serve as a portfolio project demonstrating advanced C++ skills

