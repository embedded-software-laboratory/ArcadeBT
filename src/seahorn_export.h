#ifndef SEAHORN_EXPORT
#define SEAHORN_EXPORT

#include <ostream>
#include <set>
#include <string>

#include "ir/bt.h"

namespace arcade::output {

// TODO add information about VariableManager into Behavior tree (shared_ptr? vm contains variables which are part of BTs)

void print(std::ostream &out, std::shared_ptr<arcade::ir::Node> root, std::shared_ptr<arcade::ir::VariableManager> vm);    


void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::Node> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);

void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::Node> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);

void PrintLocation(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Location> location, std::shared_ptr<arcade::ir::Location> limit, int indentation, std::shared_ptr<arcade::ir::VariableManager> vm);

void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Statement> statement, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanAssignment> statement, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::IntegerAssignment> statement, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::AssertStatement> statement, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::ReturnStatement> statement, std::shared_ptr<arcade::ir::VariableManager> vm);

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Expression> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::UnaryArithmeticOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryArithmeticOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::UnaryBooleanOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryBooleanOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryArithmeticComparisionOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanLiteral> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::ArithmeticLiteral> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanVariable> expression, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::IntegerVariable> expression, std::shared_ptr<arcade::ir::VariableManager> vm);

void PrintIndentation(std::ostream &out, int indentation);

std::set<std::shared_ptr<arcade::ir::Location>> ReachableLocations(std::shared_ptr<arcade::ir::Location> location);

void PrintMain(std::ostream &out, std::shared_ptr<arcade::ir::Node> root, std::shared_ptr<arcade::ir::VariableManager> vm);

void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::Node> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);
void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm);

} // namespace arcade::export



#endif // SEAHORN_EXPORT