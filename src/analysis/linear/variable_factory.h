#ifndef ANALYSIS_LINEAR_VARIABLE_FACTORY
#define ANALYSIS_LINEAR_VARIABLE_FACTORY

#include <memory>

#include "../../ir/cfa.h"
#include "../../ir/visitor.h"

namespace arcade::analysis::linear
{

class Encoding;

class VariableFactory : public arcade::ir::NodeVisitor {
public:
    VariableFactory(std::shared_ptr<Encoding> encoding);

    virtual void Visit(arcade::ir::SequenceNode *node);
    virtual void Visit(arcade::ir::SelectorNode *node);
    virtual void Visit(arcade::ir::ParallelNode *node);
    virtual void Visit(arcade::ir::ActionNode *node);
    virtual void Visit(arcade::ir::ConditionNode *node);

    void CreateGlobalVariables();
private:
    std::shared_ptr<Encoding> encoding_;

    void CreateLocalVariables(std::shared_ptr<arcade::ir::Cfa> cfa, unsigned node_id);
};
    
} // namespace arcade::analysis::linear


#endif // ANALYSIS_LINEAR_VARIABLE_FACTORY