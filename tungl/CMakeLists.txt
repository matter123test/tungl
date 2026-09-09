find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE "SOURCE_FILES" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE "HEADER_FILES" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_library(tungl "${SOURCE_FILES}" "${HEADER_FILES}")
set_property(TARGET tungl PROPERTY CXX_STANDARD 20)

set("GLAD_DIR" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad")
target_sources(tungl PUBLIC
	"${GLAD_DIR}/src/glad.c"
)
target_include_directories(tungl PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/"
	"${GLAD_DIR}/include/"
)

target_link_libraries(tungl PUBLIC glfw spdlog::spdlog_header_only glm::glm)
target_compile_definitions(tungl PUBLIC GLFW_INCLUDE_NONE)