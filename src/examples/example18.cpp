#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example18() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto i = variable_manager->AddGlobalIntegerVariable("i", 0, AccessType::kWrite);
    auto v = variable_manager->AddGlobalIntegerVariable("v", 0, AccessType::kWrite);
    auto s = variable_manager->AddGlobalIntegerVariable("s", 0, AccessType::kWrite);

    auto nd = variable_manager->AddGlobalIntegerVariable("nd", 0, AccessType::kRead);
    auto n = variable_manager->AddGlobalIntegerVariable("n", 0, AccessType::kWrite);

    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(n, nd);
        handle->AddAssignment(i, 0);
        handle->AddAssignment(s, 0);
        handle->AddAssignment(v, 0);
        auto [then_handle, else_handle] = handle->AddIf(n == 0 | n < 0);
        then_handle->AddReturn(ReturnValue::kFailure);
        else_handle->AddReturn(ReturnValue::kSuccess);

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
        handle->AddAssignment(v, nd);
        auto [then_handle, else_handle] = handle->AddIf(v < 0);
        {
            then_handle->AddReturn(ReturnValue::kRunning);
        }
        {
            else_handle->AddAssignment(s, s + v);
            else_handle->AddAssignment(i, i + 1);
            auto [then_handle2, else_handle2] = else_handle->AddIf(i == n);
            then_handle2->AddReturn(ReturnValue::kSuccess);
            else_handle2->AddReturn(ReturnValue::kRunning);
        }
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // condition node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(v <= s & s >= 0);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto condition_node4 = std::make_shared<ConditionNode>(builder.GetCfa()); 

    
    // sequence loop
    std::initializer_list<std::shared_ptr<Node>> children = {condition_node2, action_node3};
    auto sequence_node5 = std::make_shared<SequenceNode>(false, children);

    // root
    children = {action_node1, sequence_node5, condition_node4};
    auto sequence_node0 = std::make_shared<SequenceNode>(true, children);
    
    return {sequence_node0, variable_manager};
}
    
} 