set(ARCADE_SOURCE_FILES
    analysis/clause.cpp
    analysis/predicate.cpp
    analysis/variable.cpp

    analysis/linear/encoding.cpp
    analysis/linear/variable_factory.cpp

    ir/bt.cpp
    ir/cfa.cpp
    ir/expression.cpp
    ir/statement.cpp
    ir/variable.cpp
    ir/visitor.cpp

    examples/example00.cpp
    examples/example01.cpp
    examples/example02.cpp
    examples/example03.cpp
    examples/example04.cpp
    examples/example05.cpp
    examples/example06.cpp
    examples/example07.cpp
    examples/example08.cpp
    examples/example09.cpp
    examples/example10.cpp
    examples/example11.cpp
    examples/example12.cpp
    examples/example13.cpp
    examples/example14.cpp
    examples/example15.cpp
    examples/example16.cpp
    examples/example17.cpp
    examples/example18.cpp
    examples/example19.cpp
    examples/example20.cpp
    examples/example21.cpp
    examples/example22.cpp
    examples/example23.cpp
    examples/example24.cpp
    examples/example25.cpp
    examples/example26.cpp
    examples/example27.cpp
    examples/example28.cpp
    examples/example29.cpp
    examples/example30.cpp
    examples/example31.cpp
    examples/example32.cpp
    examples/example33.cpp
    examples/example34.cpp
    examples/example35.cpp
    examples/example36.cpp
    examples/example37.cpp
    examples/example38.cpp
    examples/example39.cpp
    examples/example40.cpp
    examples/example41.cpp
    examples/example42.cpp

    c_output.cpp
    linear_encoding.cpp
)

add_library(arcade STATIC ${ARCADE_SOURCE_FILES})
target_link_libraries(arcade ${Z3_LIBRARIES} glog)
target_include_directories(arcade PRIVATE ${Z3_CXX_INCLUDE_DIRS})
set_property(TARGET arcade PROPERTY CXX_STANDARD 17)