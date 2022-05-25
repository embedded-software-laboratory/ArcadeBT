#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example14() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 1, AccessType::kWrite);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 1, AccessType::kWrite);


    auto r1 = variable_manager->AddGlobalBooleanVariable("r1", false, AccessType::kRead);
    auto r2 = variable_manager->AddGlobalBooleanVariable("r2", false, AccessType::kWrite);

    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(x >= y);
        handle->AddAssignment(r2, r1);

        auto [then_handle, else_handle] = handle->AddIf(r2);
        {
            then_handle->AddAssignment(x, x + 1);
            then_handle->AddAssignment(y, y + 1);
        }

        handle->AddAssignment(r2, r1);
        auto [then_handle2, else_handle2] = handle->AddIf(r2);
        then_handle2->AddReturn(ReturnValue::kSuccess);
        else_handle2->AddReturn(ReturnValue::kFailure);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());    

    // action node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(x, x + 1);
        handle->AddReturn(ReturnValue::kSuccess);

    }
    auto action_node2 = std::make_shared<ActionNode>(builder.GetCfa());   


    // sequence (root)
    std::initializer_list<std::shared_ptr<Node>> children = {action_node1, action_node2};
    auto sequence_node0 = std::make_shared<SequenceNode>(false, children);
    

    return {sequence_node0, variable_manager};
}
    
} 