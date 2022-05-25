#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example27() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 0, AccessType::kWrite);
    auto i = variable_manager->AddGlobalIntegerVariable("i", 0, AccessType::kWrite);
    auto j = variable_manager->AddGlobalIntegerVariable("j", 0, AccessType::kWrite);
    auto flag = variable_manager->AddGlobalBooleanVariable("flag", false, AccessType::kWrite);


    auto nd = variable_manager->AddGlobalBooleanVariable("nd", false, AccessType::kRead);
    auto n = variable_manager->AddGlobalBooleanVariable("n", false, AccessType::kWrite);


    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(x, 0);
        handle->AddAssignment(y, 0);
        handle->AddAssignment(j, 0);
        handle->AddAssignment(i, 0);
        handle->AddAssignment(flag, nd);
        handle->AddReturn(ReturnValue::kSuccess);

    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // condidation node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(n, nd);
        auto [then_handle, else_handle] = handle->AddIf(n);
        then_handle->AddReturn(ReturnValue::kFailure);
        else_handle->AddReturn(ReturnValue::kSuccess);

    }
    auto condition_node2 = std::make_shared<ConditionNode>(builder.GetCfa());

    // action node 3
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(x, x + 1);
        handle->AddAssignment(y, y + 1);
        handle->AddAssignment(i, x + i);
        handle->AddAssignment(j, y + j);
        auto [then_handle, else_handle] = handle->AddIf(flag);
        {
            then_handle->AddAssignment(j, j + 1);
        }
        handle->AddReturn(ReturnValue::kRunning);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(j >= i);
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