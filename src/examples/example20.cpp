#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example20() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);
    auto i = variable_manager->AddGlobalIntegerVariable("i", 0, AccessType::kWrite);

    auto nd = variable_manager->AddGlobalIntegerVariable("nd", 0, AccessType::kRead);
    auto n = variable_manager->AddGlobalIntegerVariable("n", 0, AccessType::kWrite);


    // action node 1
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(x, nd);
        auto [then_handle, else_handle] = handle->AddIf(x > 0);
        then_handle->AddReturn(ReturnValue::kSuccess);
        else_handle->AddReturn(ReturnValue::kFailure);
    }
    auto action_node1 = std::make_shared<ActionNode>(builder.GetCfa());

    // action node 2
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(i, x);
        auto body_handle = handle->AddWhile(i < x);
        {
            body_handle->AddAssert(i != 0);
            body_handle->AddAssignment(i, i + 1);
        }
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node2 = std::make_shared<ActionNode>(builder.GetCfa());

    // sequence (root)
    std::initializer_list<std::shared_ptr<Node>> children = {action_node1, action_node2};
    auto sequence_node0 = std::make_shared<SequenceNode>(false, children);

    return {sequence_node0, variable_manager};
}
    
} 