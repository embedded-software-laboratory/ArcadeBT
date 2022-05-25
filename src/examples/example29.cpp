#include "example01.h"

namespace arcade::example {


// unsat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example29() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto w = variable_manager->AddGlobalIntegerVariable("w", 0, AccessType::kWrite);
    auto z = variable_manager->AddGlobalIntegerVariable("z", 0, AccessType::kWrite);
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 0, AccessType::kWrite);



    auto nd = variable_manager->AddGlobalBooleanVariable("nd", false, AccessType::kRead);
    auto n = variable_manager->AddGlobalBooleanVariable("n", false, AccessType::kWrite);


    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(w, 1);
        handle->AddAssignment(z, 0);
        handle->AddAssignment(x, 0);
        handle->AddAssignment(y, 0);
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
        handle->AddAssignment(n, nd);
        auto body_handle = handle->AddWhile(n);
        {
            auto [then_handle, else_handle] = body_handle->AddIf(w % 2 == 1);
            {
                then_handle->AddAssignment(x, x + 1);
            }
            auto [then_handle2, else_handle2] = body_handle->AddIf(z % 2 == 0);
            {
                then_handle2->AddAssignment(y, y + 1);
            }

        }
        handle->AddAssignment(z, x + y);
        handle->AddAssignment(w, z + 1);
        handle->AddReturn(ReturnValue::kRunning);
    }
    auto action_node3 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 4
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(x != y);
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