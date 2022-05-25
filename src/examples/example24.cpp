#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example24() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto old = variable_manager->AddGlobalIntegerVariable("old", 0, AccessType::kWrite);
    auto ne = variable_manager->AddGlobalIntegerVariable("new", 0, AccessType::kWrite);
    auto lock = variable_manager->AddGlobalIntegerVariable("lock", 0, AccessType::kWrite);

    auto nd = variable_manager->AddGlobalBooleanVariable("nd", false, AccessType::kRead); // TODO rename to b
    auto n = variable_manager->AddGlobalBooleanVariable("n", false, AccessType::kWrite);


    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(old, 0);
        handle->AddAssignment(lock, 0);
        handle->AddAssignment(ne, old + 1);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // condidation node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(ne != old);
        then_handle->AddReturn(ReturnValue::kFailure);
        else_handle->AddReturn(ReturnValue::kSuccess);

    }
    auto condition_node2 = std::make_shared<ConditionNode>(builder.GetCfa());

    // action node 3
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(lock, 1);
        handle->AddAssignment(old, ne);
        handle->AddAssignment(n, nd);
        auto [then_handle, else_handle] = handle->AddIf(n);
        {
            then_handle->AddAssignment(lock, 0);
            then_handle->AddAssignment(ne, ne + 1);
        }
        handle->AddReturn(ReturnValue::kRunning);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(lock != 0);
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