#include "example01.h"

namespace arcade::example {

// unsat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example04() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);
    auto crit = variable_manager->AddGlobalBooleanVariable("crit", false, AccessType::kWrite);

    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(!crit);
        handle->AddAssignment(crit, true);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [if_handle, else_handle] = handle->AddIf(x < 3);
        if_handle->AddAssignment(x, x + 1);
        if_handle->AddReturn(ReturnValue::kRunning);
        else_handle->AddAssignment(x, 0);
        else_handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node2 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 3
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(crit);
        handle->AddAssignment(crit, false);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // sequence (root)
    std::initializer_list<std::shared_ptr<Node>> children = {action_node1, action_node2, action_node3};
    auto sequence_node = std::make_shared<SequenceNode>(false, children);

    return {sequence_node, variable_manager};
}
    
} 