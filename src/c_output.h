#ifndef C_OUTPUT
#define C_OUTPUT

#include <memory>
#include <ostream>
#include <set>

#include "ir/bt.h"
#include "ir/variable.h"

namespace arcade::output{

class COutput {
public:
    COutput(std::shared_ptr<arcade::ir::Node> root, std::shared_ptr<arcade::ir::VariableManager> vm);

    void Print(std::ostream &out);
private:
    std::shared_ptr<arcade::ir::Node> root_;
    std::shared_ptr<arcade::ir::VariableManager> vm_;

    void PrintHeader(std::ostream &out);
    void PrintGlobalVariables(std::ostream &out);

    void PrintLocalVariables(std::ostream &out);
    void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::Node> node);
    void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node);
    void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node);
    void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node);
    void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node);
    void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node);

    void PrintCfas(std::ostream &out);
    void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::Node> node);
    void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node);
    void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node);
    void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node);
    void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node);
    void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node);

    void PrintLocation(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Location> location, std::shared_ptr<arcade::ir::Location> limit, int indentation);

    void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Statement> statement);
    void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanAssignment> statement);
    void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::IntegerAssignment> statement);
    void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::AssertStatement> statement);
    void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::ReturnStatement> statement);

    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Expression> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::UnaryArithmeticOperation> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryArithmeticOperation> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::UnaryBooleanOperation> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryBooleanOperation> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryArithmeticComparisionOperation> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanLiteral> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::ArithmeticLiteral> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanVariable> expression);
    void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::IntegerVariable> expression);

    void PrintIndentation(std::ostream &out, int indentation);

    std::set<std::shared_ptr<arcade::ir::Location>> ReachableLocations(std::shared_ptr<arcade::ir::Location> location);

    void PrintMain(std::ostream &out);
};

}



#endif // C_OUTPUT