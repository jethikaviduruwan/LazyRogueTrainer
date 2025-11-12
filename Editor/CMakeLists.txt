add_executable(LRTEditor
    src/EditorApp.cpp
    src/EditorLayer.cpp
    src/SceneHierarchyPanel.cpp
    src/ComponentInspector.cpp
)

target_include_directories(LRTEditor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(LRTEditor PRIVATE LRTEngine)
