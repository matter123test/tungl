add_executable(sandbox_tgl "src/main.cpp" "src/gui/DebugUI.cpp" "src/gui/DebugUI.h")
set_property(TARGET sandbox_tgl PROPERTY CXX_STANDARD 20)


target_include_directories(sandbox_tgl PRIVATE sandbox_tgl "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(sandbox_tgl PRIVATE tungl)

add_custom_command(
    TARGET sandbox_tgl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/"
    "$<TARGET_FILE_DIR:sandbox_tgl>"
)