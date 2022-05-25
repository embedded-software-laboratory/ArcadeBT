#include "example01.h"

namespace arcade::example {

// unsat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example00() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kRead);
    auto y = variable_manager->AddGlobalIntegerVariable("y", 0, AccessType::kWrite);  

    // action node 0
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(y, x);
        handle->AddAssert(y == 0);
        handle->AddReturn(ReturnValue::kSuccess);
    }
    auto action_node0 = std::make_shared<ActionNode>(builder.GetCfa());



    return {action_node0, variable_manager};
}
    
} 