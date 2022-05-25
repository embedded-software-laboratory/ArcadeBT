#include "example01.h"

#include <iostream>

namespace arcade::example {

// unsat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example02() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);

    // condition node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(x >= 0 & x <= 10);
        auto [if_handle, else_handle] = handle->AddIf(x <= 10);
        if_handle->AddReturn(ReturnValue::kSuccess);
        else_handle->AddReturn(ReturnValue::kFailure);
    }
    auto condition_node = std::make_shared<ConditionNode>(builder.GetCfa());

    // action node 1
    builder = CfaBuilder();
    {
        auto handle  = builder.AddInitialLocation();
        handle->AddAssignment(x, x + 1);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node = std::make_shared<ActionNode>(builder.GetCfa());

    // sequence (root)
    std::initializer_list<std::shared_ptr<Node>> children = {condition_node, action_node};
    auto sequence_node = std::make_shared<SequenceNode>(false, children);

    return {sequence_node, variable_manager};
}
    
} 