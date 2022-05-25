#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example33() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto w = variable_manager->AddGlobalBooleanVariable("w", 0, AccessType::kWrite);
    auto z = variable_manager->AddGlobalBooleanVariable("z", 0, AccessType::kWrite);
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 0, AccessType::kWrite);

    auto nd = variable_manager->AddGlobalIntegerVariable("nd", false, AccessType::kRead);
    auto n = variable_manager->AddGlobalIntegerVariable("n", false, AccessType::kWrite);

    auto fd = variable_manager->AddGlobalBooleanVariable("fd", false, AccessType::kRead);
    auto f = variable_manager->AddGlobalBooleanVariable("f", false, AccessType::kWrite);


    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(x, 0);
        handle->AddAssignment(y, 0);
        handle->AddAssignment(w, true);
        handle->AddAssignment(z, false);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // condidation node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(f, fd);
        auto [then_handle, else_handle] = handle->AddIf(f);
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
        auto [then_handle, else_handle] = handle->AddIf(w);
        {
            then_handle->AddAssignment(x, x + 1);
            then_handle->AddAssignment(w, !w);
        }
        auto [then_handle2, else_handle2] = handle->AddIf(!z);
        {
            then_handle2->AddAssignment(y, y + 1);
            then_handle2->AddAssignment(z, !z);
        }
        handle->AddReturn(ReturnValue::kRunning);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(x == y);
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