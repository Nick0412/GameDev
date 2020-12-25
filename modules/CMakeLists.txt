add_subdirectory(CoreGL)

add_executable(main main.cpp)
target_link_libraries(main glad glfw)