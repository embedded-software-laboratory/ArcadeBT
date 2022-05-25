add_executable(arcade_test 
    ir/expression_test.cpp
    examples_test.cpp)

target_include_directories(arcade_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(arcade_test GTest::GTest GTest::Main arcade)

set_property(TARGET arcade_test PROPERTY CXX_STANDARD 17)

gtest_discover_tests(arcade_test)
