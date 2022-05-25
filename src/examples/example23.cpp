#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example23() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto i = variable_manager->AddGlobalIntegerVariable("i", 0, AccessType::kWrite);
    auto j = variable_manager->AddGlobalIntegerVariable("j", 0, AccessType::kWrite);
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 0, AccessType::kWrite);

    auto nd = variable_manager->AddGlobalIntegerVariable("nd", 0, AccessType::kRead);
    auto n = variable_manager->AddGlobalIntegerVariable("n", 0, AccessType::kWrite);


    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(i, nd);
        handle->AddAssignment(j, nd);
        auto [then_handle, else_handle] = handle->AddIf(i > 0 & j > 0);
        {
            then_handle->AddAssignment(x, i);
            then_handle->AddAssignment(y, j);
            then_handle->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle->AddReturn(ReturnValue::kFailure);
        }
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // condidation node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(x != 0);
        then_handle->AddReturn(ReturnValue::kFailure);
        else_handle->AddReturn(ReturnValue::kSuccess);
    }
    auto condition_node2 = std::make_shared<ConditionNode>(builder.GetCfa());

    // action node 3
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(x, x - 1);
        handle->AddAssignment(y, y - 1);
        handle->AddReturn(ReturnValue::kRunning);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(i == j);
        {
            then_handle->AddAssert(y == 0);
        }
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