#include "example01.h"

namespace arcade::example {

// unsat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example21() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto a = variable_manager->AddGlobalIntegerVariable("a", 0, AccessType::kWrite);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 0, AccessType::kWrite);

    auto nd = variable_manager->AddGlobalIntegerVariable("nd", 0, AccessType::kRead);
    auto n = variable_manager->AddGlobalIntegerVariable("n", 0, AccessType::kWrite);


    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(a, nd);
        handle->AddAssignment(y, 0);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // condidation node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(a != 0);
        then_handle->AddReturn(ReturnValue::kFailure);
        else_handle->AddReturn(ReturnValue::kSuccess);
    }
    auto condition_node2 = std::make_shared<ConditionNode>(builder.GetCfa());

    // action node 3
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(y, 1);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // condidation node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(y == 0);
        then_handle->AddReturn(ReturnValue::kFailure);
        else_handle->AddReturn(ReturnValue::kSuccess);
    }
    auto condition_node4 = std::make_shared<ConditionNode>(builder.GetCfa());

    // action node 5
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(a != 0);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node5 = std::make_shared<ActionNode>(builder.GetCfa());

    // first if
    std::initializer_list<std::shared_ptr<Node>> children = {condition_node2, action_node3};
    auto selector_node6 = std::make_shared<SelectorNode>(false, children);    

    // second if
    children = {condition_node4, action_node5};
    auto selector_node7 = std::make_shared<SelectorNode>(false, children);  

    // sequence (root)
    children = {action_node1, selector_node6, selector_node7};
    auto sequence_node0 = std::make_shared<SequenceNode>(false, children);

    return {sequence_node0, variable_manager};
}
    
} 