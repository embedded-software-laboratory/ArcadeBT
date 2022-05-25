#include "encoding.h"



namespace arcade::analysis::linear
{

// static
std::shared_ptr<Encoding> Encoding::Encode(std::shared_ptr<arcade::ir::VariableManager> vm, std::shared_ptr<arcade::ir::Node> root) {
    auto encoding = std::shared_ptr<Encoding>(new Encoding(vm));

   // create z3 variables
   VariableFactory variable_factory (encoding);
   variable_factory.CreateGlobalVariables();
   root->Accept(variable_factory);

   // create z3 predicates
   // create initialization formula
   // create clauses
   //   - loop
   //   - control flow
   //  - initialization

    return encoding;
}


// Encoding
Encoding::Encoding(std::shared_ptr<arcade::ir::VariableManager> vm)
    : vm_(vm) {
}


} // namespace arcade::analysis::linear