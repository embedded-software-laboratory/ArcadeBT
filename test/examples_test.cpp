#include <sstream>

#include <gtest/gtest.h>

#include "examples/example01.h"
#include "linear_encoding.h"

TEST(Benchmark, Example0) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example00();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example1) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example01();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example2) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example02();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example3) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example03();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example4) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example04();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example5) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example05();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example6) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example06();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example7) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example07();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example8) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example08();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example9) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example09();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example10) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example10();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example11) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example11();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example12) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example12();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example13) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example13();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example14) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example14();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example15) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example15();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example16) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example16();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example17) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example17();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example18) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example18();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example19) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example19();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example20) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example20();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example21) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example21();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example22) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example22();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, DISABLED_Example23) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example23();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example24) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example24();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example25) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example25();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example26) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example26();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, DISABLED_Example27) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example27();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example28) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example28();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example29) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example29();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example30) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example30();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example31) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example31();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, DISABLED_Example32) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example32();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example33) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example33();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example34) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example34();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example35) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example35();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example36) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example36();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, DISABLED_Example37) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example37();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, DISABLED_Example38) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example38();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, DISABLED_Example39) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example39();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example40) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example40();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

TEST(Benchmark, Example41) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example41();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::unsat);
}

TEST(Benchmark, Example42) {
    using namespace arcade::ir;
    auto [root, vm] = arcade::example::example42();
    auto encoding = arcade::analysis::LinearEncoding(root, vm);
    auto solver = encoding.Solver();
    auto result = solver.check();
    EXPECT_EQ(result, z3::check_result::sat);
}

