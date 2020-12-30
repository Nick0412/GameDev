add_compile_definitions(SHADER_DIR="${CMAKE_SOURCE_DIR}/resources/shaders/")

add_library(CoreGL STATIC 
    VertexModel.cpp
    "Program.cpp"
)
target_include_directories(CoreGL PUBLIC .)
target_link_libraries(CoreGL glad)