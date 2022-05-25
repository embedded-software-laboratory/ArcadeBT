#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example17() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto k = variable_manager->AddGlobalIntegerVariable("k", 1, AccessType::kWrite);
    auto i = variable_manager->AddGlobalIntegerVariable("i", 1, AccessType::kWrite);
    auto j = variable_manager->AddGlobalIntegerVariable("j", 0, AccessType::kWrite);
    auto init = variable_manager->AddGlobalBooleanVariable("init", false, AccessType::kWrite);

    auto nd = variable_manager->AddGlobalIntegerVariable("nd", 0, AccessType::kRead);
    auto n = variable_manager->AddGlobalIntegerVariable("n", 0, AccessType::kWrite);

    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(!init);
        then_handle->AddAssignment(n, nd);
        then_handle->AddAssignment(init, true);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());    

    // condition node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(i < n);
        then_handle->AddReturn(ReturnValue::kSuccess);
        else_handle->AddReturn(ReturnValue::kFailure);
    }
    auto condition_node2 = std::make_shared<ConditionNode>(builder.GetCfa());  

    // action node 3 
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(j, 0);
        handle->AddReturn(ReturnValue::kSuccess);

    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // condition node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(j < i);
        then_handle->AddReturn(ReturnValue::kSuccess);
        else_handle->AddReturn(ReturnValue::kFailure);
    }
    auto condition_node4 = std::make_shared<ConditionNode>(builder.GetCfa()); 

    // action node 5
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(k, k + (i - j));
        handle->AddAssignment(j, j + 1);
        auto [then_handle, else_handle] = handle->AddIf(i == j);
        then_handle->AddReturn(ReturnValue::kSuccess);
        else_handle->AddReturn(ReturnValue::kRunning);

    }
    auto action_node5 = std::make_shared<ActionNode>(builder.GetCfa());

    // condition node 6
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(k >= n);
        handle->AddReturn(ReturnValue::kSuccess);

    }
    auto condition_node6 = std::make_shared<ConditionNode>(builder.GetCfa()); 

    
    // sequence inner loop
    std::initializer_list<std::shared_ptr<Node>> children = {condition_node4, action_node5};
    auto sequence_node7 = std::make_shared<SequenceNode>(false, children);

    // sequence outer loop
    children = {condition_node2, action_node3, sequence_node7};
    auto sequence_node8 = std::make_shared<SequenceNode>(true, children);

    // check assert
    children = {sequence_node8, condition_node6};
    auto selector_node9 = std::make_shared<SelectorNode>(false, children);

    // root
    children = {action_node1, selector_node9};
    auto sequence_node0 = std::make_shared<SequenceNode>(false, children);
    

    return {sequence_node0, variable_manager};
}
    
} 