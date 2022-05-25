#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example09() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 0, AccessType::kWrite);

    // condition node 1
    CfaBuilder builder;
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(x == y);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto condition_node1 = std::make_shared<ConditionNode>(builder.GetCfa());    

    // action node 3
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(x, x + 1);
        handle->AddReturn(ReturnValue::kSuccess);

    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(y, y + 1);
        handle->AddReturn(ReturnValue::kSuccess);

    }
    auto action_node4 = std::make_shared<ActionNode>(builder.GetCfa());


    // parallel
    std::initializer_list<std::shared_ptr<Node>> children = {action_node3, action_node4};
    auto parellel_node2 = std::make_shared<ParallelNode>(2, children);

    // sequence (root)
    children = {condition_node1, parellel_node2};
    auto sequence_node0 = std::make_shared<SequenceNode>(false, children);

    return {sequence_node0, variable_manager};
}
    
} 