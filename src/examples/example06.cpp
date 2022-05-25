#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example06() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 1, AccessType::kWrite);

    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(1 <= x & x <= 3);
        auto [if_handle, else_handle] = handle->AddIf(x == 1);
        if_handle->AddAssignment(x, 3);
        if_handle->AddReturn(ReturnValue::kSuccess);
        else_handle->AddReturn(ReturnValue::kFailure);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(2 <= x & x <= 3);
        auto [if_handle, else_handle] = handle->AddIf(x == 2);
        if_handle->AddAssignment(x, 1);
        if_handle->AddReturn(ReturnValue::kSuccess);
        else_handle->AddReturn(ReturnValue::kFailure);
    }
    auto action_node2 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 3
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(3 <= x & x <= 3);
        auto [if_handle, else_handle] = handle->AddIf(x == 3);
        if_handle->AddAssignment(x, 2);
        if_handle->AddReturn(ReturnValue::kSuccess);
        else_handle->AddReturn(ReturnValue::kFailure);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // sequence (root)
    std::initializer_list<std::shared_ptr<Node>> children = {action_node1, action_node2, action_node3};
    auto sequence_node = std::make_shared<SelectorNode>(false, children);

    return {sequence_node, variable_manager};
}
    
} 