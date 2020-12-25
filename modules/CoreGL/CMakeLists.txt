add_library(CoreGL STATIC VertexModel.cpp)
target_include_directories(CoreGL PUBLIC .)
target_link_libraries(CoreGL glad)