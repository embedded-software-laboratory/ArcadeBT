#include "seahorn_export.h"

#include <algorithm>
#include <queue>

namespace arcade::output {




void print(std::ostream &out, std::shared_ptr<arcade::ir::Node> root, std::shared_ptr<arcade::ir::VariableManager> vm) {
    // include bt
    out << "#include \"bt.h\"\n";
    out << "\n";

    // print assert macro
    out << "extern void __VERIFIER_error (void);\n";
    out << "#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))\n";
    out << "\n";

    // global variables
    for (auto var : vm->GetGlobalBooleanVariables()) {
        if (!vm->IsGlobal(var)) {
            continue;
        } 
        out << "bool global_" << var->Name() << " = " << var->GetInitialValue() << ";\n";
    }
    for (auto var : vm->GetGlobalIntegerVariables()) {
        if (!vm->IsGlobal(var)) {
            continue;
        } 
        out << "int global_" << var->Name() << " = " << var->GetInitialValue() << ";\n";
    }
    out << "\n";

    // local variables
    PrintLocalVariables(out, root, vm);
    PrintCfa(out, root, vm);
    PrintMain(out, root, vm);
}

void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::Node> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    auto sequence_node = std::dynamic_pointer_cast<arcade::ir::SequenceNode>(node);
    if (sequence_node) {
        PrintLocalVariables(out, sequence_node, vm);
    }
    auto selector_node = std::dynamic_pointer_cast<arcade::ir::SelectorNode>(node);
    if (selector_node) {
        PrintLocalVariables(out, selector_node, vm);
    }
    auto parallel_node = std::dynamic_pointer_cast<arcade::ir::ParallelNode>(node);
    if (parallel_node) {
        PrintLocalVariables(out, parallel_node, vm);
    }
    auto action_node = std::dynamic_pointer_cast<arcade::ir::ActionNode>(node);
    if (action_node) {
        PrintLocalVariables(out, action_node, vm);
    }
    auto condition_node = std::dynamic_pointer_cast<arcade::ir::ConditionNode>(node);
    if (condition_node) {
        PrintLocalVariables(out, condition_node, vm);
    }
    // TODO check of completeness
}

void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintLocalVariables(out, child, vm);
    }
}

void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintLocalVariables(out, child, vm);
    }
}

void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintLocalVariables(out, child, vm);
    }
}

void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto var : vm->GetLocalBooleanVariables(node->GetCfa())) {
        out << "bool " << "node_" << std::to_string(node->GetId()) << "_" << var->Name() << " = " << var->GetInitialValue() << "\n";
    }
}

void PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto var : vm->GetLocalIntegerVariables(node->GetCfa())) {
        out << "int " << "node_" << std::to_string(node->GetId()) << "_" << var->Name() << " = " << var->GetInitialValue() << "\n";
    }
}



void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::Node> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    auto sequence_node = std::dynamic_pointer_cast<arcade::ir::SequenceNode>(node);
    if (sequence_node) {
        PrintCfa(out, sequence_node, vm);
    }
    auto selector_node = std::dynamic_pointer_cast<arcade::ir::SelectorNode>(node);
    if (selector_node) {
        PrintCfa(out, selector_node, vm);
    }
    auto parallel_node = std::dynamic_pointer_cast<arcade::ir::ParallelNode>(node);
    if (parallel_node) {
        PrintCfa(out, parallel_node, vm);
    }
    auto action_node = std::dynamic_pointer_cast<arcade::ir::ActionNode>(node);
    if (action_node) {
        PrintCfa(out, action_node, vm);
    }
    auto condition_node = std::dynamic_pointer_cast<arcade::ir::ConditionNode>(node);
    if (condition_node) {
        PrintCfa(out, condition_node, vm);
    }
    // TODO check of completeness
}

void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintCfa(out, child, vm);
    }
}

void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintCfa(out, child, vm);
    }
}

void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintCfa(out, child, vm);
    }
}

void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << "return_t cfa" << std::to_string(node->GetId()) << "(struct node_t *node) {\n";
    PrintLocation(out, "node_" + std::to_string(node->GetId()) + "_", node->GetCfa()->GetInitialLocation(), nullptr, 2, vm);
    out << "}\n";
    out << "\n";
}

void PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << "return_t cfa" << std::to_string(node->GetId()) << "(struct node_t *node) {\n";
    PrintLocation(out, "node_" + std::to_string(node->GetId()) + "_", node->GetCfa()->GetInitialLocation(), nullptr, 2, vm);
    out << "}\n";
    out << "\n";
}

void PrintLocation(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Location> location, std::shared_ptr<arcade::ir::Location> limit,  int indentation, std::shared_ptr<arcade::ir::VariableManager> vm) {
    // if (location == limit) {
    //     return;
    // }
    
    // auto nr_transitions = location->GetTransitions().size();
    // if (nr_transitions == 1) {
    //     auto transition = location->GetTransitions().front();
    //     PrintIndentation(out, indentation);
    //     PrintStatement(out, variable_prefix, transition->GetStatement(), vm);
    //     PrintLocation(out, variable_prefix, transition->ToLocation().lock(), limit, indentation, vm);
    // } else if (nr_transitions == 2) {
    //     auto primary_transition = location->GetTransitions().at(0);
    //     auto secondary_transition = location->GetTransitions().at(1);

    //     auto primary_statement = std::dynamic_pointer_cast<arcade::ir::AssumeStatement>(primary_transition->GetStatement());
    //     auto secondary_statement = std::dynamic_pointer_cast<arcade::ir::AssumeStatement>(secondary_transition->GetStatement());
    //     if (!primary_statement || !secondary_statement) {
    //         out << "ERROR 1\n"; // TODO
    //     }
    //     if (!primary_statement->IsPrimaryBanch() || secondary_statement->IsPrimaryBanch()) {
    //         out << "ERROR 2\n"; // TODO
    //     }

    //     if (primary_statement->GetBranchType() == arcade::ir::BranchType::kIf) {
    //         PrintIndentation(out, indentation);
    //         out << "if (";
    //         PrintExpression(out, variable_prefix, primary_statement->GetCondition(), vm);
    //         out << ") {\n";

    //         auto reach_if = ReachableLocations(primary_transition->ToLocation().lock());
    //         auto reach_else = ReachableLocations(secondary_transition->ToLocation().lock());

    //         // out << "if:\n";
    //         // for (auto loc: reach_if) {
    //         //     out << loc->GetId() << ", ";
    //         // }
    //         // out << "\n";
    //         // out << "else:\n";
    //         // for (auto loc: reach_else) {
    //         //     out << loc->GetId() << ", ";
    //         // }
    //         // out << "\n";
            
    //         std::vector<std::shared_ptr<arcade::ir::Location>> intersection;
    //         std::set_intersection(reach_if.begin(), reach_if.end(),
    //             reach_else.begin(), reach_else.end(),
    //             std::back_inserter(intersection));
            
    //         std::shared_ptr<arcade::ir::Location> new_limit;
    //         if (intersection.empty()) {
    //             new_limit = nullptr;
    //         } else {
    //             new_limit  = intersection.front();
    //         }

    //         PrintLocation(out, variable_prefix, primary_transition->ToLocation().lock(), new_limit, indentation+2, vm);
            
    //         PrintIndentation(out, indentation);
    //         out << "} else {\n";
    //         PrintLocation(out, variable_prefix, secondary_transition->ToLocation().lock(), new_limit, indentation+2, vm);
    //         PrintIndentation(out, indentation);
    //         out << "}\n";            

    //     } else if (primary_statement->GetBranchType() == arcade::ir::BranchType::kWhile) {
    //         PrintIndentation(out, indentation);
    //         out << "while (";
    //         PrintExpression(out, variable_prefix,primary_statement->GetCondition(), vm);
    //         out << ") {\n";

    //         PrintLocation(out, variable_prefix, primary_transition->ToLocation().lock(), location, indentation+2, vm);
    //         out << "}\n";
    //         PrintLocation(out, variable_prefix, secondary_transition->ToLocation().lock(), limit, indentation, vm);
    //     } else {
    //         out << "ERROR 3\n"; // TODO
    //     }

    // } else if (nr_transitions == 0) {
    //     return; // 
    // } else {
    //     // TODO exception
    //     out << "error!";
    // }
}


void PrintIndentation(std::ostream &out, int indentation) {
    for (int i=0; i < indentation; ++i) {
        out << " ";
    }
}

void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Statement> statement, std::shared_ptr<arcade::ir::VariableManager> vm) {
    auto boolean_assign_statement = std::dynamic_pointer_cast<arcade::ir::BooleanAssignment>(statement);
    if (boolean_assign_statement) {
        PrintStatement(out, variable_prefix, boolean_assign_statement, vm);
    }
    auto integer_assign_statement = std::dynamic_pointer_cast<arcade::ir::IntegerAssignment>(statement);
    if (integer_assign_statement) {
        PrintStatement(out, variable_prefix, integer_assign_statement, vm);
    }
    auto assert_statement = std::dynamic_pointer_cast<arcade::ir::AssertStatement>(statement);
    if (assert_statement) {
        PrintStatement(out, variable_prefix, assert_statement, vm);
    }
    auto return_statement = std::dynamic_pointer_cast<arcade::ir::ReturnStatement>(statement);
    if (return_statement) {
        PrintStatement(out, variable_prefix, return_statement, vm);
    }
    // TODO check completeness + error?
}

void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanAssignment> statement, std::shared_ptr<arcade::ir::VariableManager> vm) {
    PrintExpression(out, variable_prefix, statement->Variable(), vm);
    out << " = ";
    PrintExpression(out, variable_prefix, statement->Expression(), vm);
    out << ";\n";
}

void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::IntegerAssignment> statement, std::shared_ptr<arcade::ir::VariableManager> vm) {
    PrintExpression(out, variable_prefix, statement->Variable(), vm);
    out << " = ";
    PrintExpression(out, variable_prefix, statement->Expression(), vm);
    out << ";\n";
}

void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::AssertStatement> statement, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << "sassert(";
    PrintExpression(out, variable_prefix, statement->GetCondition(), vm);
    out << ");\n";
}

void PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::ReturnStatement> statement, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << "return ";
    switch (statement->GetReturnValue())
    {
    case arcade::ir::ReturnValue::kSuccess:
        out << "SUCCESS";
        break;
    case arcade::ir::ReturnValue::kRunning:
        out << "RUNNING";
        break;
    case arcade::ir::ReturnValue::kFailure:
        out << "FAILURE";
        break;    
    default:
        break;
    }
    out << ";\n";
}


void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Expression> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    auto unary_arith_op = std::dynamic_pointer_cast<arcade::ir::UnaryArithmeticOperation>(expression);
    if (unary_arith_op) {
        PrintExpression(out, variable_prefix, unary_arith_op, vm);
    }
    auto binary_arith_op = std::dynamic_pointer_cast<arcade::ir::BinaryArithmeticOperation>(expression);
    if (binary_arith_op) {
        PrintExpression(out, variable_prefix, binary_arith_op, vm);
    }
    auto unary_bool_op = std::dynamic_pointer_cast<arcade::ir::UnaryBooleanOperation>(expression);
    if (unary_bool_op) {
        PrintExpression(out, variable_prefix, unary_bool_op, vm);
    }
    auto binary_bool_op = std::dynamic_pointer_cast<arcade::ir::BinaryBooleanOperation>(expression);
    if (binary_bool_op) {
        PrintExpression(out, variable_prefix, binary_bool_op, vm);
    }
    auto binary_cmp_op = std::dynamic_pointer_cast<arcade::ir::BinaryArithmeticComparisionOperation>(expression);
    if (binary_cmp_op) {
        PrintExpression(out, variable_prefix, binary_cmp_op, vm);
    }
    auto bool_lit = std::dynamic_pointer_cast<arcade::ir::BooleanLiteral>(expression);
    if (bool_lit) {
        PrintExpression(out, variable_prefix, bool_lit, vm);
    }
    auto arith_lit = std::dynamic_pointer_cast<arcade::ir::ArithmeticLiteral>(expression);
    if (arith_lit) {
        PrintExpression(out, variable_prefix, arith_lit, vm);
    }
    auto bool_var = std::dynamic_pointer_cast<arcade::ir::BooleanVariable>(expression);
    if (bool_var) {
        PrintExpression(out, variable_prefix, bool_var, vm);
    }
    auto int_var = std::dynamic_pointer_cast<arcade::ir::IntegerVariable>(expression);
    if (int_var) {
        PrintExpression(out, variable_prefix, int_var, vm);
    }

    // TODO check completeness + error?
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::UnaryArithmeticOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    switch (expression->Operator())
    {
    case arcade::ir::UnaryArithmeticOperator::kMinus:
        out << "-";
        break;
    default:
        break;
    }
    out << "(";
    PrintExpression(out, variable_prefix, expression->Operand(), vm);
    out << ")";
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryArithmeticOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << "(";
    PrintExpression(out, variable_prefix, expression->LhsOperand(), vm);
    out << ")";

    switch (expression->Operator())
    {
    case arcade::ir::BinaryArithmeticOperator::kAddition:
        out << "+";
        break;
    case arcade::ir::BinaryArithmeticOperator::kDivision:
        out << "/";
        break;
    case arcade::ir::BinaryArithmeticOperator::kMultiplication:
        out << "*";
        break;
    case arcade::ir::BinaryArithmeticOperator::kSubstraction:
        out << "-";
        break;    
    default:
        break;
    }

    out << "(";
    PrintExpression(out, variable_prefix, expression->RhsOperand(), vm);
    out << ")";
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::UnaryBooleanOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    switch (expression->Operator())
    {
    case arcade::ir::UnaryBooleanOperator::kNegation:
        out << "!";
        break;
    default:
        break;
    }
    out << "(";
    PrintExpression(out, variable_prefix, expression->Operand(), vm);
    out << ")";
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryBooleanOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    // no implication operator in c
    if (expression->Operator() == arcade::ir::BinaryBooleanOperator::kImplication) { // TODO nicer
        out << "!(";
    } else {
        out << "(";
    }
    
    PrintExpression(out, variable_prefix, expression->LhsOperand(), vm);
    out << ")";

    switch (expression->Operator())
    {
    case arcade::ir::BinaryBooleanOperator::kConjunction :
        out << "&&";
        break;
    case arcade::ir::BinaryBooleanOperator::kDisjunction:
        out << "||";
        break;
    case arcade::ir::BinaryBooleanOperator::kExclusiveOr:
        out << "^";
        break;
    case arcade::ir::BinaryBooleanOperator::kImplication:
        out << "||";
        break;    
    default:
        break;
    }

    out << "(";
    PrintExpression(out, variable_prefix, expression->RhsOperand(), vm);
    out << ")";
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryArithmeticComparisionOperation> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << "(";
    PrintExpression(out, variable_prefix, expression->LhsOperand(), vm);
    out << ")";

    switch (expression->Operator())
    {
    case arcade::ir::BinaryArithmeticComparisionOperator::kEqual:
        out << "==";
        break;
    case arcade::ir::BinaryArithmeticComparisionOperator::kGreater:
        out << ">";
        break;
    case arcade::ir::BinaryArithmeticComparisionOperator::kGreaterOrEqual:
        out << ">=";
        break;
    case arcade::ir::BinaryArithmeticComparisionOperator::kLess:
        out << "<";
        break; 
    case arcade::ir::BinaryArithmeticComparisionOperator::kLessOrEqual:
        out << "<=";
        break;  
    case arcade::ir::BinaryArithmeticComparisionOperator::kUnequal:
        out << "!=";
        break;     
    default:
        break;
    }

    out << "(";
    PrintExpression(out, variable_prefix, expression->RhsOperand(), vm);
    out << ")";
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanLiteral> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << expression->Value();
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::ArithmeticLiteral> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << expression->Value();
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanVariable> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    if (vm->IsGlobal(expression)) {
        out << "global_" + expression->Name();
    } else {
        out << variable_prefix + expression->Name();
    }
}

void PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::IntegerVariable> expression, std::shared_ptr<arcade::ir::VariableManager> vm) {
    if (vm->IsGlobal(expression)) {
        out << "global_" + expression->Name();
    } else {
        out << variable_prefix + expression->Name();
    }
}

std::set<std::shared_ptr<arcade::ir::Location>> ReachableLocations(std::shared_ptr<arcade::ir::Location> location) {
    std::queue<std::shared_ptr<arcade::ir::Location>> todo;
    std::set<std::shared_ptr<arcade::ir::Location>> reachable_states;
    todo.push(location);

    while (!todo.empty()) {
        auto loc =  todo.front();
        todo.pop();

        if (reachable_states.find(loc) != reachable_states.end()) {
            continue;
        }
        reachable_states.insert(loc);

        for (auto transition : loc->GetTransitions()) {
            todo.push(transition->ToLocation().lock());
        }
    }
    return reachable_states;
}

void PrintMain(std::ostream &out, std::shared_ptr<arcade::ir::Node> root, std::shared_ptr<arcade::ir::VariableManager> vm) {
    out << "\n";
    out << "int main() {\n";
    PrintStructs(out, root, vm);

    auto root_name = "node" + std::to_string(root->GetId());
    out << "  while (1) {\n";
    out << "    " << root_name << ".func_ptr(&" << root_name << ");\n";
    out << "  }\n";
    out << "}\n";
    out << "\n";
}

void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::Node> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    auto sequence_node = std::dynamic_pointer_cast<arcade::ir::SequenceNode>(node);
    if (sequence_node) {
        PrintStructs(out, sequence_node, vm);
    }
    auto selector_node = std::dynamic_pointer_cast<arcade::ir::SelectorNode>(node);
    if (selector_node) {
        PrintStructs(out, selector_node, vm);
    }
    auto parallel_node = std::dynamic_pointer_cast<arcade::ir::ParallelNode>(node);
    if (parallel_node) {
        PrintStructs(out, parallel_node, vm);
    }
    auto action_node = std::dynamic_pointer_cast<arcade::ir::ActionNode>(node);
    if (action_node) {
        PrintStructs(out, action_node, vm);
    }
    auto condition_node = std::dynamic_pointer_cast<arcade::ir::ConditionNode>(node);
    if (condition_node) {
        PrintStructs(out, condition_node, vm);
    }
    // TODO check of completeness    
}

void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintStructs(out, child, vm);
    }

    auto node_name = "node" + std::to_string(node->GetId());
    out << "  struct node_t " << node_name << "; \n";
    out << "  " << node_name << ".type = SEQUENCE;\n";
    out << "  " << node_name << ".func_ptr = &sequence_tick;\n";
    out << "  " << node_name << ".memory = " << node->GetMemory() << ";\n";
    out << "  struct node_t " << node_name << "_children[" << node->GetChildren().size() << "] = {";
    for (auto child : node->GetChildren()) {
        auto child_name = "node" + std::to_string(child->GetId());
        out << child_name;
        if (child != node->GetChildren().back()) {
            out << ", ";
        }
        
    }
    out << "};\n";
    out << "  " << node_name << ".children = " << node_name << "_children;\n";
    out << "  " << node_name << ".size = " << node->GetChildren().size() << ";\n";
    out << "\n";
}

void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintStructs(out, child, vm);
    }
    auto node_name = "node" + std::to_string(node->GetId());
    out << "  struct node_t " << node_name << "; \n";
    out << "  " << node_name << ".type = SELECTOR;\n";
    out << "  " << node_name << ".func_ptr = &sequence_tick;\n";
    out << "  " << node_name << ".memory = " << node->GetMemory() << ";\n";
    out << "  struct node_t " << node_name << "_children[" << node->GetChildren().size() << "] = {";
    for (auto child : node->GetChildren()) {
        auto child_name = "node" + std::to_string(child->GetId());
        out << child_name;
        if (child != node->GetChildren().back()) {
            out << ", ";
        }
        
    }
    out << "};\n";
    out << "  " << node_name << ".children = " << node_name << "_children;\n";
    out << "  " << node_name << ".size = " << node->GetChildren().size() << ";\n";
    out << "\n";
}

void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    for (auto child : node->GetChildren()) {
        PrintStructs(out, child, vm);
    }
    out << "error: parallel nodes are not supported\n";
    // TODO
}

void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    auto node_name = "node" + std::to_string(node->GetId());
    out << "  struct node_t " << node_name << "; \n";
    out << "  " << node_name << ".type = ACTION;\n";
    out << "  " << node_name << ".func_ptr = &cfa" << std::to_string(node->GetId()) <<  ";\n";
    out << "\n";
}

void PrintStructs(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node, std::shared_ptr<arcade::ir::VariableManager> vm) {
    auto node_name = "node" + std::to_string(node->GetId());
    out << "  struct node_t " << node_name << "; \n";
    out << "  " << node_name << ".type = ACTION;\n";
    out << "  " << node_name << ".func_ptr = &cfa" << std::to_string(node->GetId()) <<  ";\n";
    out << "\n";
}


}