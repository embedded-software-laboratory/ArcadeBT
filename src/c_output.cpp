#include "c_output.h"

#include <algorithm>
#include <exception>
#include <queue>

namespace arcade::output{

COutput::COutput(std::shared_ptr<arcade::ir::Node> root, std::shared_ptr<arcade::ir::VariableManager> vm)
    : root_(root), vm_(vm) {
}


void COutput::Print(std::ostream &out) {
    PrintHeader(out);
    PrintGlobalVariables(out);
    PrintLocalVariables(out);
    PrintCfas(out);
    PrintMain(out);
}

void COutput::PrintHeader(std::ostream &out) {
    out << "extern void __VERIFIER_error (void);\n";
    out << "#define sassert(X) (void)((X) || (__VERIFIER_error (), 0))\n";
    out << "\n";
    out << "extern int nd(void);\n";
    out << "\n";
}

void COutput::PrintGlobalVariables(std::ostream &out) {
    out << "// global variables\n";
    for (auto var : vm_->GetGlobalBooleanVariables()) {
        if (!vm_->IsGlobal(var)) { // TODO still needed
            continue;
        } 
        out << "int global_" << var->Name() << " = " << var->GetInitialValue() << ";\n"; // TODO c int instead of bool
    }
    for (auto var : vm_->GetGlobalIntegerVariables()) {
        if (!vm_->IsGlobal(var)) { // TODO still needed
            continue;
        } 
        out << "int global_" << var->Name() << " = " << var->GetInitialValue() << ";\n";
    }
    out << "\n";

}

void COutput::PrintLocalVariables(std::ostream &out) {
    out << "// local variables\n";
    PrintLocalVariables(out, root_);
    out << "\n";
}

void COutput::PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::Node> node) {
    auto sequence_node = std::dynamic_pointer_cast<arcade::ir::SequenceNode>(node);
    if (sequence_node) {
        PrintLocalVariables(out, sequence_node);
    }
    auto selector_node = std::dynamic_pointer_cast<arcade::ir::SelectorNode>(node);
    if (selector_node) {
        PrintLocalVariables(out, selector_node);
    }
    auto parallel_node = std::dynamic_pointer_cast<arcade::ir::ParallelNode>(node);
    if (parallel_node) {
        throw std::logic_error("no export for parallel nodes available");
        PrintLocalVariables(out, parallel_node);
    }
    auto action_node = std::dynamic_pointer_cast<arcade::ir::ActionNode>(node);
    if (action_node) {
        PrintLocalVariables(out, action_node);
    }
    auto condition_node = std::dynamic_pointer_cast<arcade::ir::ConditionNode>(node);
    if (condition_node) {
        PrintLocalVariables(out, condition_node);
    }
    // TODO check of completeness
}

void COutput::PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node) {
    for (auto child : node->GetChildren()) {
        PrintLocalVariables(out, child);
    }

    if (node->GetMemory()) {
        out << "node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(node->GetChildren().front()->GetId()) << ";\n";
    }
}

void COutput::PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node) {
    for (auto child : node->GetChildren()) {
        PrintLocalVariables(out, child);
    }

    if (node->GetMemory()) {
        out << "node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(node->GetChildren().front()->GetId()) << ";\n";
    }
}

void COutput::PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node) {
    for (auto child : node->GetChildren()) {
        PrintLocalVariables(out, child);
    }
    // TODO error
}

void COutput::PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node) {
    for (auto var : vm_->GetLocalBooleanVariables(node->GetCfa())) {
        out << "int " << "node_" << std::to_string(node->GetId()) << "_" << var->Name() << " = " << var->GetInitialValue() << "\n"; // TODO bool to int ?
    }
}

void COutput::PrintLocalVariables(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node) {
    for (auto var : vm_->GetLocalIntegerVariables(node->GetCfa())) {
        out << "int " << "node_" << std::to_string(node->GetId()) << "_" << var->Name() << " = " << var->GetInitialValue() << "\n";
    }
}

void COutput::PrintCfas(std::ostream &out) {
    out << "// cfas\n";
    PrintCfa(out, root_);
}

void COutput::PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::Node> node) {
    auto sequence_node = std::dynamic_pointer_cast<arcade::ir::SequenceNode>(node);
    if (sequence_node) {
        PrintCfa(out, sequence_node);
    }
    auto selector_node = std::dynamic_pointer_cast<arcade::ir::SelectorNode>(node);
    if (selector_node) {
        PrintCfa(out, selector_node);
    }
    auto parallel_node = std::dynamic_pointer_cast<arcade::ir::ParallelNode>(node);
    if (parallel_node) {
        PrintCfa(out, parallel_node);
    }
    auto action_node = std::dynamic_pointer_cast<arcade::ir::ActionNode>(node);
    if (action_node) {
        PrintCfa(out, action_node);
    }
    auto condition_node = std::dynamic_pointer_cast<arcade::ir::ConditionNode>(node);
    if (condition_node) {
        PrintCfa(out, condition_node);
    }
    // TODO check of completeness
}

void COutput::PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::SequenceNode> node) {
    for (auto child : node->GetChildren()) {
        PrintCfa(out, child);
    }
    int ind_offset = 0;
    if (node->GetMemory()) {
        ind_offset = 2;
    }

    out << "int node" << std::to_string(node->GetId()) << "() {\n";
    out << "  int status;\n";
    for (int i = 0; i < node->GetChildren().size(); ++i) {
        auto child = node->GetChildren().at(i);

        if (node->GetMemory()) {
            PrintIndentation(out, 2);
            out << "if (node_" << std::to_string(node->GetId()) << "_next == " << std::to_string(child->GetId()) <<") {\n";
        }
        PrintIndentation(out, 2+ind_offset);
        out << "status = node" << std::to_string(child->GetId()) <<  "();\n";

        // running
        PrintIndentation(out, 2+ind_offset);
        out << "if (status == 1) {\n";
        if (node->GetMemory()) {
            PrintIndentation(out, 4+ind_offset);
            out << "node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(child->GetId()) << ";\n"; 
        }
        PrintIndentation(out, 4+ind_offset);
        out << "return 1;\n";
        PrintIndentation(out, 2+ind_offset);
        out << "}\n";

        // failure
        PrintIndentation(out, 2+ind_offset);
        out << "if (status == 2) {\n";
        if (node->GetMemory()) {
            PrintIndentation(out, 4+ind_offset);
            out << "node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(node->GetChildren().front()->GetId()) << ";\n"; 
        }
        PrintIndentation(out, 4+ind_offset);
        out << "return 2;\n";
        PrintIndentation(out, 2+ind_offset);
        out << "}\n";

        // success
        if (node->GetMemory() && i != node->GetChildren().size() - 1) {
            PrintIndentation(out, 2+ind_offset);
            out << "node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(node->GetChildren().at(i+1)->GetId()) << ";\n"; 
        }  
        if (node->GetMemory()) {
            PrintIndentation(out, 2);
            out << "}\n";
        }    
        out << "\n";  
    }
    if (node->GetMemory()) {
        out << "  node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(node->GetChildren().front()->GetId()) << ";\n"; 
    }
    out << "  return 0;\n";
    out << "}\n";
    out << "\n";
}

void COutput::PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::SelectorNode> node) {
    for (auto child : node->GetChildren()) {
        PrintCfa(out, child);
    }

    int ind_offset = 0;
    if (node->GetMemory()) {
        ind_offset = 2;
    }

    out << "int node" << std::to_string(node->GetId()) << "() {\n";
    out << "  int status;\n";
    for (int i = 0; i < node->GetChildren().size(); ++i) {
        auto child = node->GetChildren().at(i);

        if (node->GetMemory()) {
            PrintIndentation(out, 2);
            out << "if (node_" << std::to_string(node->GetId()) << "_next == " << std::to_string(child->GetId()) <<") {\n";
        }
        PrintIndentation(out, 2+ind_offset);
        out << "status = node" << std::to_string(child->GetId()) <<  "();\n";

        // running
        PrintIndentation(out, 2+ind_offset);
        out << "if (status == 1) {\n";
        if (node->GetMemory()) {
            PrintIndentation(out, 4+ind_offset);
            out << "node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(child->GetId()) << ";\n"; 
        }
        PrintIndentation(out, 4+ind_offset);
        out << "return 1;\n";
        PrintIndentation(out, 2+ind_offset);
        out << "}\n";

        // success
        PrintIndentation(out, 2+ind_offset);
        out << "if (status == 0) {\n";
        if (node->GetMemory()) {
            PrintIndentation(out, 4+ind_offset);
            out << "node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(node->GetChildren().front()->GetId()) << ";\n"; 
        }
        PrintIndentation(out, 4+ind_offset);
        out << "return 0;\n";
        PrintIndentation(out, 2+ind_offset);
        out << "}\n";

        // failure
        if (node->GetMemory() && i != node->GetChildren().size() - 1) {
            PrintIndentation(out, 2+ind_offset);
            out << "node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(node->GetChildren().at(i+1)->GetId()) << ";\n"; 
        }   
        if (node->GetMemory()) {
            PrintIndentation(out, 2);
            out << "}\n";
        }

        out << "\n";   
    }
    if (node->GetMemory()) {
        out << "  node_" << std::to_string(node->GetId()) << "_next = " << std::to_string(node->GetChildren().front()->GetId()) << ";\n"; 
    }
    out << "  return 2;\n";
    out << "}\n";
    out << "\n";
}

void COutput::PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ParallelNode> node) {
    for (auto child : node->GetChildren()) {
        PrintCfa(out, child);
    }
    // TODO error
}

void COutput::PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ActionNode> node) {
    out << "int node" << std::to_string(node->GetId()) << "() {\n";
    PrintLocation(out, "node_" + std::to_string(node->GetId()) + "_", node->GetCfa()->GetInitialLocation(), nullptr, 2);
    out << "}\n";
    out << "\n";
}

void COutput::PrintCfa(std::ostream &out, std::shared_ptr<arcade::ir::ConditionNode> node) {
    out << "int node" << std::to_string(node->GetId()) << "() {\n";
    PrintLocation(out, "node_" + std::to_string(node->GetId()) + "_", node->GetCfa()->GetInitialLocation(), nullptr, 2);
    out << "}\n";
    out << "\n";
}


// FIXME broken due to new builder and branchstatement
void COutput::PrintLocation(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Location> location, std::shared_ptr<arcade::ir::Location> limit,  int indentation) {
    if (location == limit) {
        return;
    }
    
    auto nr_transitions = location->GetTransitions().size();
    if (nr_transitions == 1) {
        auto transition = location->GetTransitions().front();
        PrintIndentation(out, indentation);
        PrintStatement(out, variable_prefix, transition->GetStatement());
        PrintLocation(out, variable_prefix, transition->ToLocation().lock(), limit, indentation);
    } else if (nr_transitions == 2) {
        auto primary_transition = location->GetTransitions().at(0);
        auto secondary_transition = location->GetTransitions().at(1);

        auto primary_statement = std::dynamic_pointer_cast<arcade::ir::BranchStatement>(primary_transition->GetStatement());
        auto secondary_statement = std::dynamic_pointer_cast<arcade::ir::BranchStatement>(secondary_transition->GetStatement());
        if (!primary_statement || !secondary_statement) {
            out << "ERROR 1\n"; // TODO
        }
        if (!primary_statement->IsPrimaryBanch() || secondary_statement->IsPrimaryBanch()) {
            out << "ERROR 2\n"; // TODO
        }

        if (primary_statement->GetBranchType() == arcade::ir::BranchType::kIf) {
            PrintIndentation(out, indentation);
            out << "if (";
            PrintExpression(out, variable_prefix, primary_statement->GetCondition());
            out << ") {\n";

            auto reach_if = ReachableLocations(primary_transition->ToLocation().lock());
            auto reach_else = ReachableLocations(secondary_transition->ToLocation().lock());

            // out << "if:\n";
            // for (auto loc: reach_if) {
            //     out << loc->GetId() << ", ";
            // }
            // out << "\n";
            // out << "else:\n";
            // for (auto loc: reach_else) {
            //     out << loc->GetId() << ", ";
            // }
            // out << "\n";
            
            std::vector<std::shared_ptr<arcade::ir::Location>> intersection;
            std::set_intersection(reach_if.begin(), reach_if.end(),
                reach_else.begin(), reach_else.end(),
                std::back_inserter(intersection));
            
            std::shared_ptr<arcade::ir::Location> new_limit;
            if (intersection.empty()) {
                new_limit = nullptr;
            } else {
                new_limit  = intersection.front();
            }

            PrintLocation(out, variable_prefix, primary_transition->ToLocation().lock(), new_limit, indentation+2);
            
            PrintIndentation(out, indentation);
            out << "} else {\n";
            PrintLocation(out, variable_prefix, secondary_transition->ToLocation().lock(), new_limit, indentation+2);
            PrintIndentation(out, indentation);
            out << "}\n";            

        } else if (primary_statement->GetBranchType() == arcade::ir::BranchType::kWhile) {
            PrintIndentation(out, indentation);
            out << "while (";
            PrintExpression(out, variable_prefix,primary_statement->GetCondition());
            out << ") {\n";

            PrintLocation(out, variable_prefix, primary_transition->ToLocation().lock(), location, indentation+2);
            out << "}\n";
            PrintLocation(out, variable_prefix, secondary_transition->ToLocation().lock(), limit, indentation);
        } else {
            out << "ERROR 3\n"; // TODO
        }

    } else if (nr_transitions == 0) {
        return; // 
    } else {
        // TODO exception
        out << "error!";
    }
}


void COutput::PrintIndentation(std::ostream &out, int indentation) {
    for (int i=0; i < indentation; ++i) {
        out << " ";
    }
}

void COutput::PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Statement> statement) {
    auto boolean_assign_statement = std::dynamic_pointer_cast<arcade::ir::BooleanAssignment>(statement);
    if (boolean_assign_statement) {
        PrintStatement(out, variable_prefix, boolean_assign_statement);
    }
    auto integer_assign_statement = std::dynamic_pointer_cast<arcade::ir::IntegerAssignment>(statement);
    if (integer_assign_statement) {
        PrintStatement(out, variable_prefix, integer_assign_statement);
    }
    auto assert_statement = std::dynamic_pointer_cast<arcade::ir::AssertStatement>(statement);
    if (assert_statement) {
        PrintStatement(out, variable_prefix, assert_statement);
    }
    auto return_statement = std::dynamic_pointer_cast<arcade::ir::ReturnStatement>(statement);
    if (return_statement) {
        PrintStatement(out, variable_prefix, return_statement);
    }
    // TODO check completeness + error?
}

void COutput::PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanAssignment> statement) {
    PrintExpression(out, variable_prefix, statement->Variable());
    out << " = ";
    PrintExpression(out, variable_prefix, statement->Expression());
    out << ";\n";
}

void COutput::PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::IntegerAssignment> statement) {
    PrintExpression(out, variable_prefix, statement->Variable());
    out << " = ";
    PrintExpression(out, variable_prefix, statement->Expression());
    out << ";\n";
}

void COutput::PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::AssertStatement> statement) {
    out << "sassert(";
    PrintExpression(out, variable_prefix, statement->GetCondition());
    out << ");\n";
}

void COutput::PrintStatement(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::ReturnStatement> statement) {
    out << "return ";
    switch (statement->GetReturnValue())
    {
    case arcade::ir::ReturnValue::kSuccess:
        out << "0";
        break;
    case arcade::ir::ReturnValue::kRunning:
        out << "1";
        break;
    case arcade::ir::ReturnValue::kFailure:
        out << "2";
        break;    
    default:
        break;
    }
    out << ";\n";
}


void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::Expression> expression) {
    auto unary_arith_op = std::dynamic_pointer_cast<arcade::ir::UnaryArithmeticOperation>(expression);
    if (unary_arith_op) {
        PrintExpression(out, variable_prefix, unary_arith_op);
    }
    auto binary_arith_op = std::dynamic_pointer_cast<arcade::ir::BinaryArithmeticOperation>(expression);
    if (binary_arith_op) {
        PrintExpression(out, variable_prefix, binary_arith_op);
    }
    auto unary_bool_op = std::dynamic_pointer_cast<arcade::ir::UnaryBooleanOperation>(expression);
    if (unary_bool_op) {
        PrintExpression(out, variable_prefix, unary_bool_op);
    }
    auto binary_bool_op = std::dynamic_pointer_cast<arcade::ir::BinaryBooleanOperation>(expression);
    if (binary_bool_op) {
        PrintExpression(out, variable_prefix, binary_bool_op);
    }
    auto binary_cmp_op = std::dynamic_pointer_cast<arcade::ir::BinaryArithmeticComparisionOperation>(expression);
    if (binary_cmp_op) {
        PrintExpression(out, variable_prefix, binary_cmp_op);
    }
    auto bool_lit = std::dynamic_pointer_cast<arcade::ir::BooleanLiteral>(expression);
    if (bool_lit) {
        PrintExpression(out, variable_prefix, bool_lit);
    }
    auto arith_lit = std::dynamic_pointer_cast<arcade::ir::ArithmeticLiteral>(expression);
    if (arith_lit) {
        PrintExpression(out, variable_prefix, arith_lit);
    }
    auto bool_var = std::dynamic_pointer_cast<arcade::ir::BooleanVariable>(expression);
    if (bool_var) {
        PrintExpression(out, variable_prefix, bool_var);
    }
    auto int_var = std::dynamic_pointer_cast<arcade::ir::IntegerVariable>(expression);
    if (int_var) {
        PrintExpression(out, variable_prefix, int_var);
    }

    // TODO check completeness + error?
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::UnaryArithmeticOperation> expression) {
    switch (expression->Operator())
    {
    case arcade::ir::UnaryArithmeticOperator::kMinus:
        out << "-";
        break;
    default:
        break;
    }
    out << "(";
    PrintExpression(out, variable_prefix, expression->Operand());
    out << ")";
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryArithmeticOperation> expression) {
    out << "(";
    PrintExpression(out, variable_prefix, expression->LhsOperand());
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
    case arcade::ir::BinaryArithmeticOperator::kModulo:
        out << "%";
        break;   
    default:
        break;
    }

    out << "(";
    PrintExpression(out, variable_prefix, expression->RhsOperand());
    out << ")";
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::UnaryBooleanOperation> expression) {
    switch (expression->Operator())
    {
    case arcade::ir::UnaryBooleanOperator::kNegation:
        out << "!";
        break;
    default:
        break;
    }
    out << "(";
    PrintExpression(out, variable_prefix, expression->Operand());
    out << ")";
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryBooleanOperation> expression) {
    // no implication operator in c
    if (expression->Operator() == arcade::ir::BinaryBooleanOperator::kImplication) { // TODO nicer
        out << "!(";
    } else {
        out << "(";
    }
    
    PrintExpression(out, variable_prefix, expression->LhsOperand());
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
    PrintExpression(out, variable_prefix, expression->RhsOperand());
    out << ")";
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BinaryArithmeticComparisionOperation> expression) {
    out << "(";
    PrintExpression(out, variable_prefix, expression->LhsOperand());
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
    PrintExpression(out, variable_prefix, expression->RhsOperand());
    out << ")";
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanLiteral> expression) {
    out << expression->Value();
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::ArithmeticLiteral> expression) {
    out << expression->Value();
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::BooleanVariable> expression) {
    if (vm_->IsGlobal(expression)) {
        if (expression->GetAccessType() == arcade::ir::AccessType::kRead) {
            out << "nd()";
        } else {
            out << "global_" + expression->Name();
        } 
    } else {
        out << variable_prefix + expression->Name();
    }
}

void COutput::PrintExpression(std::ostream &out, std::string variable_prefix, std::shared_ptr<arcade::ir::IntegerVariable> expression) {
    if (vm_->IsGlobal(expression)) {
        if (expression->GetAccessType() == arcade::ir::AccessType::kRead) {
            out << "nd()";
        } else {
            out << "global_" + expression->Name();
        } 
    } else {
        out << variable_prefix + expression->Name();
    }
}

std::set<std::shared_ptr<arcade::ir::Location>> COutput::ReachableLocations(std::shared_ptr<arcade::ir::Location> location) {
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

void COutput::PrintMain(std::ostream &out) {
    out << "int main(void) {\n";
    out << "  while (1) {\n";
    out << "    node" << std::to_string(root_->GetId()) << "();\n";
    out << "  }\n";
    out << "}\n";
    out << "\n";
}


}