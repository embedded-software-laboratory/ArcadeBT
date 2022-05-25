#ifndef ANALYSIS_LINEAR_ENCODING
#define ANALYSIS_LINEAR_ENCODING

#include <map>
#include <memory>

#include "z3++.h"

#include "variable_factory.h"
#include "../variable.h"
#include "../../ir/bt.h"
#include "../../ir/variable.h"

namespace arcade::analysis::linear
{

class Encoding {
public:
    
    static std::shared_ptr<Encoding> Encode(std::shared_ptr<arcade::ir::VariableManager> vm, std::shared_ptr<arcade::ir::Node> root);

    friend VariableFactory; 
private:
    Encoding(std::shared_ptr<arcade::ir::VariableManager> vm);

    std::shared_ptr<arcade::ir::VariableManager> vm_;

    z3::context context_;
    // maps variables from the cfas and behavior tree to z3 variables
    // TODO make to lists?

    // maps CFA variables to z3 variables
    std::map<std::shared_ptr<arcade::ir::Variable>, arcade::analysis::Variable> cfa_variable_map_;   

    // maps Sequence & Seletor Nodes to the memory variables (if needed)
    std::map<std::shared_ptr<arcade::ir::Node>, arcade::analysis::Variable> memory_variable_map;

    // maps Parallel Nodes to counter variables for success, running, failure
    std::map<std::shared_ptr<arcade::ir::Node>, arcade::analysis::Variable> count_success_variable_map;
    std::map<std::shared_ptr<arcade::ir::Node>, arcade::analysis::Variable> count_running_variable_map;
    std::map<std::shared_ptr<arcade::ir::Node>, arcade::analysis::Variable> count_failure_variable_map;

    // maps children of Parallel nodes to complete variables
    std::map<std::shared_ptr<arcade::ir::Node>, arcade::analysis::Variable> completed_variable_map;
};

} // namespace arcade::analysis::linear




#endif // ANALYSIS_LINEAR_ENCODING