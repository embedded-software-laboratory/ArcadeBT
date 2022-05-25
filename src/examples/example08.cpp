#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example08() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);

    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(x == 0 | x == 10);
        auto [if_handle, else_handle] = handle->AddIf(x == 1);
        {
            if_handle->AddReturn(ReturnValue::kFailure);
        }
        {
            auto [if_handle2, else_handle2] = else_handle->AddIf(x == 10);
            if_handle2->AddAssignment(x, 0);
            if_handle2->AddReturn(ReturnValue::kSuccess);
            else_handle2->AddReturn(ReturnValue::kFailure);
        }
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [if_handle, else_handle] = handle->AddIf(x < 10);
        if_handle->AddAssignment(x, x + 1);
        if_handle->AddReturn(ReturnValue::kRunning);
        else_handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node2 = std::make_shared<ActionNode>(builder.GetCfa());


    // sequence (root)
    std::initializer_list<std::shared_ptr<Node>> children = {action_node1, action_node2};
    auto sequence_node = std::make_shared<SelectorNode>(true, children);

    return {sequence_node, variable_manager};
}
    
} 