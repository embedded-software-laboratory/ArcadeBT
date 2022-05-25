add_executable(print print.cpp)
target_include_directories(print PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(print arcade)
set_property(TARGET print PROPERTY CXX_STANDARD 17)

add_executable(bench bench.cpp)
target_include_directories(bench PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(bench arcade)
set_property(TARGET bench PROPERTY CXX_STANDARD 17)

add_executable(c_demo c_demo.c)