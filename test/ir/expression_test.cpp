#include <sstream>

#include <gtest/gtest.h>

#include "ir/expression.h"

TEST(Expression, BooleanLiteral) {
    using namespace arcade::ir;
    BooleanLiteral lit_false(false);
    BooleanLiteral lit_true(true);

    EXPECT_EQ(lit_false.Value(), false);
    EXPECT_EQ(lit_true.Value(), true);
}

TEST(Expression, Print) {
    using namespace arcade::ir;
    auto lit_false = BooleanExpressionHandle(false);
    auto lit_true = BooleanExpressionHandle(true);

    std::stringstream ss;
    lit_false.Expression()->Print(ss);
    EXPECT_EQ(ss.str(), "false");

    ss.str("");
    lit_true.Expression()->Print(ss);
    EXPECT_EQ(ss.str(), "true");

    auto conj = lit_false & true;
    ss.str("");
    conj.Expression()->Print(ss);
    EXPECT_EQ(ss.str(), "(false) & (true)");

    auto neg = !conj;
    ss.str("");
    neg.Expression()->Print(ss);
    EXPECT_EQ(ss.str(), "!((false) & (true))");
}

