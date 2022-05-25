#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example37() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto i = variable_manager->AddGlobalIntegerVariable("i", 0, AccessType::kWrite);
    auto c = variable_manager->AddGlobalIntegerVariable("c", 0, AccessType::kWrite);


    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(i, 0);
        handle->AddAssignment(c, 0);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // condidation node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(i < 1000);
        {
            then_handle->AddReturn(ReturnValue::kFailure);
        }
        {
            else_handle->AddReturn(ReturnValue::kSuccess);
        }
    }
    auto condition_node2 = std::make_shared<ConditionNode>(builder.GetCfa());

    // action node 3
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(c, c + i);
        handle->AddAssignment(i, i + 1);
        handle->AddReturn(ReturnValue::kRunning);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(c >= 0);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node4 = std::make_shared<ActionNode>(builder.GetCfa());

    // loop
    std::initializer_list<std::shared_ptr<Node>> children = {condition_node2, action_node3};
    auto selector_node5 = std::make_shared<SelectorNode>(false, children);    

    // sequence (root)
    children = {action_node1, selector_node5, action_node4};
    auto sequence_node0 = std::make_shared<SequenceNode>(true, children);

    return {sequence_node0, variable_manager};
}
    
} 