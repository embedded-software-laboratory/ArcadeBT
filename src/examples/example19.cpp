#include "example01.h"

namespace arcade::example {

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example19() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto x = variable_manager->AddGlobalIntegerVariable("x", 0, AccessType::kWrite);


    // action node 0
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssert(x % 2 == 0);
        handle->AddAssignment(x, x + 2);
        handle->AddReturn(ReturnValue::kFailure);
    }
    auto action_node0 = std::make_shared<ActionNode>(builder.GetCfa());    


    return {action_node0, variable_manager};
}
    
} 