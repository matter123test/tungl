add_executable(sandbox_tgl "main.cpp")
set_property(TARGET sandbox_tgl PROPERTY CXX_STANDARD 20)

target_link_libraries(sandbox_tgl PRIVATE tungl)