find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE "SOURCE_FILES" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE "HEADER_FILES" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_library(tungl)
set_property(TARGET tungl PROPERTY CXX_STANDARD 20)

target_sources(tungl PUBLIC "${SOURCE_FILES}" "${HEADER_FILES}")

set("GLAD_DIR" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad")
set("IMGUI_DIR" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")

target_sources(tungl PUBLIC
	"${GLAD_DIR}/src/glad.c"

	"${IMGUI_DIR}/imconfig.h"
    "${IMGUI_DIR}/imgui.h"
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_internal.h"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp"
    "${IMGUI_DIR}/misc/cpp/imgui_stdlib.h"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.h"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.h"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
target_include_directories(tungl PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/"
	"${GLAD_DIR}/include/"

	"${IMGUI_DIR}"
	"${IMGUI_DIR}/backends"
	"${IMGUI_DIR}/misc/cpp"
)

target_link_libraries(tungl PUBLIC winmm glfw spdlog::spdlog_header_only glm::glm)
target_compile_definitions(tungl PUBLIC GLFW_INCLUDE_NONE)