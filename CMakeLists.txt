cmake_minimum_required(VERSION 3.20)
project(LazyRogueTrainer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LRT_BUILD_EDITOR "Build the editor application" ON)
option(LRT_BUILD_TESTS "Build unit tests" OFF)

add_subdirectory(Engine)

if(LRT_BUILD_EDITOR)
    add_subdirectory(Editor)
endif()

if(LRT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif()

