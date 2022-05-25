#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example16() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto p = variable_manager->AddGlobalIntegerVariable("p", 0, AccessType::kWrite);
    auto count = variable_manager->AddGlobalIntegerVariable("count", 0, AccessType::kWrite);

    auto r1 = variable_manager->AddGlobalBooleanVariable("r1", false, AccessType::kRead);
    auto r2 = variable_manager->AddGlobalBooleanVariable("r2", false, AccessType::kWrite);

    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(p <= 12);
        handle->AddAssignment(r2, r1);
        handle->AddAssignment(count, count + 1);
        auto [then_handle, else_handle] = handle->AddIf(count <= 6);
        {
            auto [then_handle2, else_handle2] = then_handle->AddIf(r2);
            then_handle2->AddReturn(ReturnValue::kSuccess);
            else_handle2->AddAssignment(p, p + 2);
            else_handle2->AddReturn(ReturnValue::kFailure);
        }
        else_handle->AddReturn(ReturnValue::kRunning);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());    

    // action node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(p, p + 1);
        handle->AddReturn(ReturnValue::kSuccess);

    }
    auto action_node2 = std::make_shared<ActionNode>(builder.GetCfa());   


    // sequence (root)
    std::initializer_list<std::shared_ptr<Node>> children = {action_node1, action_node2};
    auto sequence_node0 = std::make_shared<SequenceNode>(false, children);
    

    return {sequence_node0, variable_manager};
}
    
} 