#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example03() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 0, AccessType::kWrite);

    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(y >= 0 & x >= 0);
        auto [if_handle, else_handle] = handle->AddIf(y == 0);
        if_handle->AddAssignment(y, y + 1);
        else_handle->AddAssignment(y, y - 1);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(x, x + 1);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node2 = std::make_shared<ActionNode>(builder.GetCfa());

    // sequence (root)
    std::initializer_list<std::shared_ptr<Node>> children = {action_node1, action_node2};
    auto sequence_node = std::make_shared<SequenceNode>(false, children);

    return {sequence_node, variable_manager};
}
    
} 