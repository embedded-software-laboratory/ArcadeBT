#include "linear_encoding.h"

#include <iostream>
#include <exception>

#include <glog/logging.h>

// TODO change ids (cfa, nodes, locations) to int (needs less casting)

// TODO improve non-deterministic input handling
// TODO missing check if variable is assigned which beeing read-only
/*
    current handling of non-deterministic input:
        - using a _global_ variable with the kRead access type (for local variables this flag will be ignored) 
        - varibale should only be used once in a statement (TODO: enforce?) multiple occurences are encoded by using the same non-deterministic value twice
        - only works if used in assignment statement: e.g., x := y, where y is the non-deterministic variable 
        
        - global kRead variables are igrnoed by the initialization formula and the id helper such that the old and the new value is unrelated 
*/

namespace arcade::analysis {

LinearEncoding::LinearEncoding(std::shared_ptr<arcade::ir::Node> behavior_tree, std::shared_ptr<arcade::ir::VariableManager> variable_manager)
    : behavior_tree_(behavior_tree), variable_manager_(variable_manager), context_(), solver_(context_, "HORN"), initialization_(context_) {
    CreateVariables();
    CreatePredicates();
    CreateRules();
    CreateLoop();
    CreateInitialization();
}

z3::solver LinearEncoding::Solver() {
    return solver_;
}

// Create Variables
void LinearEncoding::CreateVariables() {
    /*
    Create all z3 variables:
        - Sequence & Selector: for memory
        - Parallel: counting and determining success condition
        - Action & Condition: global and local program variables

    Variables are created in pair for unprimed and primed version. The primed name has a "_p" suffix.
    All variables pairs are stored in variables_. The ordering in the vector is used for the predicate domains.
    */
   // create all non-global variables
   CreateVariables(behavior_tree_);
   CreateVariables(-1, nullptr); // TODO refactoring: avoid -1 as a placeholder
}

std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>> LinearEncoding::CreateIntegerVariablePair(const std::string &name) {
    auto variable = std::make_shared<z3::expr>(context_.int_const(name.c_str()));
    auto name_prime = name + "_p";
    auto variable_prime = std::make_shared<z3::expr>(context_.int_const(name_prime.c_str()));
    return std::make_pair<>(variable, variable_prime);
}

std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>> LinearEncoding::CreateBooleanVariablePair(const std::string &name) {
    auto variable = std::make_shared<z3::expr>(context_.bool_const(name.c_str()));
    auto name_prime = name + "_p";
    auto variable_prime = std::make_shared<z3::expr>(context_.bool_const(name_prime.c_str()));
    return std::make_pair<>(variable, variable_prime);
}

void LinearEncoding::CreateVariables(std::shared_ptr<arcade::ir::Node> node) {
    auto sequence_node = std::dynamic_pointer_cast<arcade::ir::SequenceNode>(node);
    if (sequence_node) {
        CreateVariables(sequence_node);
    }
    auto selector_node = std::dynamic_pointer_cast<arcade::ir::SelectorNode>(node);
    if (selector_node) {
        CreateVariables(selector_node);
    }
    auto parallel_node = std::dynamic_pointer_cast<arcade::ir::ParallelNode>(node);
    if (parallel_node) {
        CreateVariables(parallel_node);
    }
    auto action_node = std::dynamic_pointer_cast<arcade::ir::ActionNode>(node);
    if (action_node) {
        CreateVariables(action_node);
    }
    auto condition_node = std::dynamic_pointer_cast<arcade::ir::ConditionNode>(node);
    if (condition_node) {
        CreateVariables(condition_node);
    }
    // TODO check of completeness
}

void LinearEncoding::CreateVariables(std::shared_ptr<arcade::ir::SequenceNode> node) {
    if (node->GetMemory()) {
        auto variables = CreateIntegerVariablePair("node_" + std::to_string(node->GetId()) + "_memory");
        nondeterministic_[variables.first] = false;
        variables_.push_back(variables);
        memory_variable_map_[node] = variables;
        initialization_.push_back(*variables.first == static_cast<int>(node->GetChildren().front()->GetId()));
    }
    for (const auto child : node->GetChildren()) {
        CreateVariables(child);
    }
}

void LinearEncoding::CreateVariables(std::shared_ptr<arcade::ir::SelectorNode> node) {
    if (node->GetMemory()) {
        auto variables = CreateIntegerVariablePair("node_" + std::to_string(node->GetId()) + "_memory");
        nondeterministic_[variables.first] = false;
        variables_.push_back(variables);
        memory_variable_map_[node] = variables;
        initialization_.push_back(*variables.first == static_cast<int>(node->GetChildren().front()->GetId()));
    }
    for (const auto child : node->GetChildren()) {
        CreateVariables(child);
    }
}

void LinearEncoding::CreateVariables(std::shared_ptr<arcade::ir::ParallelNode> node) {
    auto success_count_variables = CreateIntegerVariablePair("node_" + std::to_string(node->GetId()) + "_success_count");
    nondeterministic_[success_count_variables.first] = false;
    variables_.push_back(success_count_variables);
    success_count_variable_map_[node] = success_count_variables;
    initialization_.push_back(*success_count_variables.first == 0);

    auto running_count_variables = CreateIntegerVariablePair("node_" + std::to_string(node->GetId()) + "_running_count");
    nondeterministic_[running_count_variables.first] = false;
    variables_.push_back(running_count_variables);
    running_count_variable_map_[node] = running_count_variables;
    initialization_.push_back(*running_count_variables.first == 0);

    auto failure_count_variables = CreateIntegerVariablePair("node_" + std::to_string(node->GetId()) + "_failure_count");
    nondeterministic_[failure_count_variables.first] = false;
    variables_.push_back(failure_count_variables);
    failure_count_variable_map_[node] = failure_count_variables;
    initialization_.push_back(*failure_count_variables.first == 0);

    for (const auto child : node->GetChildren()) {
        auto completed_variables = CreateBooleanVariablePair("node_" + std::to_string(child->GetId()) + "_completed");
        nondeterministic_[completed_variables.first] = false;
        variables_.push_back(completed_variables);
        completed_variable_map_[child] = completed_variables;
        initialization_.push_back(!*completed_variables.first);  
    }
        
    for (const auto child : node->GetChildren()) {
        CreateVariables(child);
    }
}

void LinearEncoding::CreateVariables(std::shared_ptr<arcade::ir::ActionNode> node) {
    CreateVariables(node->GetId(), node->GetCfa());
}

void LinearEncoding::CreateVariables(std::shared_ptr<arcade::ir::ConditionNode> node) {
    CreateVariables(node->GetId(), node->GetCfa());
}

// nullptr is global
void LinearEncoding::CreateVariables(int node_id, std::shared_ptr<arcade::ir::Cfa> cfa) {
    // global
    if (!cfa) {
    for (auto boolean_variable : variable_manager_->GetGlobalBooleanVariables()) {
        auto variables = CreateBooleanVariablePair("global_" + boolean_variable->Name());
        if (!cfa && boolean_variable->GetAccessType() == arcade::ir::AccessType::kRead) {
            nondeterministic_[variables.first] = true;
        } else {
            nondeterministic_[variables.first] = false;
        }
        variables_.push_back(variables);
        boolean_variable_map_[boolean_variable] = variables;
        if (boolean_variable->GetAccessType() == arcade::ir::AccessType::kWrite){
            if (boolean_variable->GetInitialValue()) {
                initialization_.push_back(*variables.first); 
            } else {
                initialization_.push_back(!*variables.first); 
            }
        }
    }

    for (auto integer_variable : variable_manager_->GetGlobalIntegerVariables()) {
        auto variables = CreateIntegerVariablePair("global_" + integer_variable->Name());
        if (!cfa && integer_variable->GetAccessType()  == arcade::ir::AccessType::kRead) {
            nondeterministic_[variables.first] = true;
        } else {
            nondeterministic_[variables.first] = false;
        }
        variables_.push_back(variables);
        integer_variable_map_[integer_variable] = variables;
        if (integer_variable->GetAccessType() == arcade::ir::AccessType::kWrite) {
            initialization_.push_back(*variables.first == integer_variable->GetInitialValue()); 
        }  
    }
    return;
    }


    // local
    for (auto boolean_variable : variable_manager_->GetLocalBooleanVariables(cfa)) {
        auto variables = CreateBooleanVariablePair("node_" + std::to_string(node_id) + "_local_" + boolean_variable->Name());
        if (!cfa && boolean_variable->GetAccessType() == arcade::ir::AccessType::kRead) {
            nondeterministic_[variables.first] = true;
        } else {
            nondeterministic_[variables.first] = false;
        }
        variables_.push_back(variables);
        boolean_variable_map_[boolean_variable] = variables;
        if (boolean_variable->GetAccessType() == arcade::ir::AccessType::kWrite){
            if (boolean_variable->GetInitialValue()) {
                initialization_.push_back(*variables.first); 
            } else {
                initialization_.push_back(!*variables.first); 
            }
        }
    }

    for (auto integer_variable : variable_manager_->GetLocalIntegerVariables(cfa)) {
        auto variables = CreateIntegerVariablePair("node_" + std::to_string(node_id) + "_local_" + integer_variable->Name());
        if (!cfa && integer_variable->GetAccessType()  == arcade::ir::AccessType::kRead) {
            nondeterministic_[variables.first] = true;
        } else {
            nondeterministic_[variables.first] = false;
        }
        variables_.push_back(variables);
        integer_variable_map_[integer_variable] = variables;
        if (integer_variable->GetAccessType() == arcade::ir::AccessType::kWrite) {
            initialization_.push_back(*variables.first == integer_variable->GetInitialValue()); 
        }  
    }
}

// predicates
void LinearEncoding::CreatePredicates() {
    /*
    Create all z3 preicates:
        - all nodes: tick, success, running, failure
        - parallel nodes: intermediate
        - cfa: for each location

    all predicates have the same/compete domain. Therefore it is not allowed to create variables after this point (TODO enforce or check)
    */
   CreatePredicates(behavior_tree_);
}

void LinearEncoding::CreatePredicates(std::shared_ptr<arcade::ir::Node> node) {
    std::string name = "tick_" + std::to_string(node->GetId());
    tick_predicate_map_[node] = std::make_shared<z3::func_decl>(z3::function(name, Domain(), context_.bool_sort()));

    name = "success_" + std::to_string(node->GetId());
    success_predicate_map_[node] = std::make_shared<z3::func_decl>(z3::function(name, Domain(), context_.bool_sort()));

    name = "running_" + std::to_string(node->GetId());
    running_predicate_map_[node] = std::make_shared<z3::func_decl>(z3::function(name, Domain(), context_.bool_sort()));

    name = "failure_" + std::to_string(node->GetId());
    failure_predicate_map_[node] = std::make_shared<z3::func_decl>(z3::function(name, Domain(), context_.bool_sort()));

    auto sequence_node = std::dynamic_pointer_cast<arcade::ir::SequenceNode>(node);
    if (sequence_node) {
        CreatePredicates(sequence_node);
    }
    auto selector_node = std::dynamic_pointer_cast<arcade::ir::SelectorNode>(node);
    if (selector_node) {
        CreatePredicates(selector_node);
    }
    auto parallel_node = std::dynamic_pointer_cast<arcade::ir::ParallelNode>(node);
    if (parallel_node) {
        CreatePredicates(parallel_node);
    }
    auto action_node = std::dynamic_pointer_cast<arcade::ir::ActionNode>(node);
    if (action_node) {
        CreatePredicates(action_node);
    }
    auto condition_node = std::dynamic_pointer_cast<arcade::ir::ConditionNode>(node);
    if (condition_node) {
        CreatePredicates(condition_node);
    }
    // TODO check of completeness
}

void LinearEncoding::CreatePredicates(std::shared_ptr<arcade::ir::SequenceNode> node) {
    for (auto child : node->GetChildren()) {
        CreatePredicates(child);
    }
}

void LinearEncoding::CreatePredicates(std::shared_ptr<arcade::ir::SelectorNode> node) {
    for (auto child : node->GetChildren()) {
        CreatePredicates(child);
    }
}

void LinearEncoding::CreatePredicates(std::shared_ptr<arcade::ir::ParallelNode> node) {
    std::string name = "intermediate_" + std::to_string(node->GetId());
    intermediate_predicate_map_[node] = std::make_shared<z3::func_decl>(z3::function(name, Domain(), context_.bool_sort()));

    for (auto child : node->GetChildren()) {
        CreatePredicates(child);
    }
}

void LinearEncoding::CreatePredicates(std::shared_ptr<arcade::ir::ActionNode> node) {
    CreatePredicates(node->GetId(), node->GetCfa());
}

void LinearEncoding::CreatePredicates(std::shared_ptr<arcade::ir::ConditionNode> node)  {
    CreatePredicates(node->GetId(), node->GetCfa());
}

void LinearEncoding::CreatePredicates(int node_id, std::shared_ptr<arcade::ir::Cfa> cfa) {
    for (auto location : cfa->GetLocations()) {
        auto name = "location_" + std::to_string(node_id) + "_" + std::to_string(location->GetId());
        location_predicate_map_[location] = std::make_shared<z3::func_decl>(z3::function(name, Domain(), context_.bool_sort()));
    }
}

z3::sort_vector LinearEncoding::Domain() {
    auto domain = z3::sort_vector(context_);
    for (auto &[var, var_prime] : variables_) {
        domain.push_back(var->get_sort());
    }
    return domain;
}


// rules
void LinearEncoding::CreateRules() {
    /*
    Create the Horn Clauses
    */
   CreateRules(behavior_tree_);
}

void LinearEncoding::CreateRules(std::shared_ptr<arcade::ir::Node> node) {
    auto sequence_node = std::dynamic_pointer_cast<arcade::ir::SequenceNode>(node);
    if (sequence_node) {
        CreateRules(sequence_node);
    }
    auto selector_node = std::dynamic_pointer_cast<arcade::ir::SelectorNode>(node);
    if (selector_node) {
        CreateRules(selector_node);
    }
    auto parallel_node = std::dynamic_pointer_cast<arcade::ir::ParallelNode>(node);
    if (parallel_node) {
        CreateRules(parallel_node);
    }
    auto action_node = std::dynamic_pointer_cast<arcade::ir::ActionNode>(node);
    if (action_node) {
        CreateRules(action_node);
    }
    auto condition_node = std::dynamic_pointer_cast<arcade::ir::ConditionNode>(node);
    if (condition_node) {
        CreateRules(condition_node);
    }
    // TODO check of completeness
}

void LinearEncoding::CreateRules(std::shared_ptr<arcade::ir::SequenceNode> node) {
    if (node->GetMemory()) {
        // tick
        for (auto child : node->GetChildren()) {
            solver_.add(z3::forall(Variables(), z3::implies(Tick(node) && *(memory_variable_map_.at(node).first) == static_cast<int>(child->GetId()), Tick(child))));
        }
        // running & failure
        for (auto child : node->GetChildren()) {
            solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Running(child) && *(memory_variable_map_.at(node).second) == static_cast<int>(child->GetId())
                && Id({memory_variable_map_.at(node).first}), RunningPrime(node))));
            solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Failure(child) && *(memory_variable_map_.at(node).second) == static_cast<int>(node->GetChildren().front()->GetId())
                && Id({memory_variable_map_.at(node).first}), FailurePrime(node))));
        }
        // success
        for (int i=0; i < node->GetChildren().size() -1; i++) {
            solver_.add(z3::forall(Variables(), z3::implies(Success(node->GetChildren().at(i)), Tick(node->GetChildren().at(i+1)))));
        }
        solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Success(node->GetChildren().back()) && *(memory_variable_map_.at(node).second) == static_cast<int>(node->GetChildren().front()->GetId())
                && Id({memory_variable_map_.at(node).first}), SuccessPrime(node))));       
    } else {
        // tick
        solver_.add(z3::forall(Variables(), z3::implies(Tick(node), Tick(node->GetChildren().front()))));
        // running & failure
        for (auto child : node->GetChildren()) {
            solver_.add(z3::forall(Variables(), z3::implies(Running(child), Running(node))));
            solver_.add(z3::forall(Variables(), z3::implies(Failure(child), Failure(node))));
        }
        // success
        for (int i=0; i < node->GetChildren().size() -1; i++) {
            solver_.add(z3::forall(Variables(), z3::implies(Success(node->GetChildren().at(i)), Tick(node->GetChildren().at(i+1)))));
        }
        solver_.add(z3::forall(Variables(), z3::implies(Success(node->GetChildren().back()), Success(node))));
    }
    
    for (auto child : node->GetChildren()) {
        CreateRules(child);
    }
}

// TODO reuse sequence encoding
void LinearEncoding::CreateRules(std::shared_ptr<arcade::ir::SelectorNode> node) {
    if (node->GetMemory()) {
        // tick
        for (auto child : node->GetChildren()) {
            solver_.add(z3::forall(Variables(), z3::implies(Tick(node) && *(memory_variable_map_.at(node).first) == static_cast<int>(child->GetId()), Tick(child))));
        }
        // running & success
        for (auto child : node->GetChildren()) {
            solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Running(child) && *(memory_variable_map_.at(node).second) == static_cast<int>(child->GetId())
                && Id({memory_variable_map_.at(node).first}), RunningPrime(node))));
            solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Success(child) && *(memory_variable_map_.at(node).second) == static_cast<int>(node->GetChildren().front()->GetId())
                && Id({memory_variable_map_.at(node).first}), SuccessPrime(node))));
        }
        // failure
        for (int i=0; i < node->GetChildren().size() -1; i++) {
            solver_.add(z3::forall(Variables(), z3::implies(Failure(node->GetChildren().at(i)), Tick(node->GetChildren().at(i+1)))));
        }
        solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Failure(node->GetChildren().back()) && *(memory_variable_map_.at(node).second) == static_cast<int>(node->GetChildren().front()->GetId())
                && Id({memory_variable_map_.at(node).first}), FailurePrime(node))));  
    } else {
        // tick
        solver_.add(z3::forall(Variables(), z3::implies(Tick(node), Tick(node->GetChildren().front()))));
        // running & success
        for (auto child : node->GetChildren()) {
            solver_.add(z3::forall(Variables(), z3::implies(Running(child), Running(node))));
            solver_.add(z3::forall(Variables(), z3::implies(Success(child), Success(node))));
        }
        // failure
        for (int i=0; i < node->GetChildren().size() -1; i++) {
            solver_.add(z3::forall(Variables(), z3::implies(Failure(node->GetChildren().at(i)), Tick(node->GetChildren().at(i+1)))));
        }
        solver_.add(z3::forall(Variables(), z3::implies(Failure(node->GetChildren().back()), Failure(node))));
    }
    
    for (auto child : node->GetChildren()) {
        CreateRules(child);
    }
}

void LinearEncoding::CreateRules(std::shared_ptr<arcade::ir::ParallelNode> node) {
    // tick
    z3::expr_vector reset_vector(context_);
    reset_vector.push_back(*(success_count_variable_map_.at(node).second) == 0);
    reset_vector.push_back(*(running_count_variable_map_.at(node).second) == 0);
    reset_vector.push_back(*(failure_count_variable_map_.at(node).second) == 0);

    std::vector<std::shared_ptr<z3::expr>> except;
    except.push_back(success_count_variable_map_.at(node).first);
    except.push_back(running_count_variable_map_.at(node).first);
    except.push_back(failure_count_variable_map_.at(node).first);

    for (auto child : node->GetChildren()) {
        reset_vector.push_back(!*(completed_variable_map_.at(child).second));
        except.push_back(completed_variable_map_.at(child).first);
    }

    auto tick_id = Id(except);
    solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Tick(node) && z3::mk_and(reset_vector) && tick_id, IntermediatePrime(node))));

    // continue
    z3::expr success_condition = *(success_count_variable_map_.at(node).first) >= node->GetThreshold();
    z3::expr failure_condition = *(failure_count_variable_map_.at(node).first) >= static_cast<int>((node->GetChildren().size() - node->GetThreshold() + 1));
    z3::expr running_condition = (*(failure_count_variable_map_.at(node).first) + *(running_count_variable_map_.at(node).first) >= static_cast<int>(node->GetChildren().size() - node->GetThreshold() + 1)) 
        && (*(success_count_variable_map_.at(node).first) + *(running_count_variable_map_.at(node).first) >= node->GetThreshold()); // TODO correct?
    z3::expr continue_expr = !success_condition && !failure_condition && !running_condition;

    for (auto child : node->GetChildren()) {
        solver_.add(z3::forall(Variables(), z3::implies(Intermediate(node) && continue_expr && !*(completed_variable_map_.at(child).first), Tick(child))));
    }

    // return
    z3::expr inc_success_expr = *(success_count_variable_map_.at(node).second)== *(success_count_variable_map_.at(node).first) + 1;
    z3::expr inc_running_expr = *(running_count_variable_map_.at(node).second)== *(running_count_variable_map_.at(node).first) + 1;
    z3::expr inc_failure_expr = *(failure_count_variable_map_.at(node).second)== *(failure_count_variable_map_.at(node).first) + 1;
    for (auto child : node->GetChildren()) {
        solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Success(child) 
            && inc_success_expr 
            && *(completed_variable_map_.at(child).second)
            && Id({success_count_variable_map_.at(node).first, completed_variable_map_.at(child).first}), IntermediatePrime(node))));
        solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Running(child) 
            && inc_running_expr 
            && *(completed_variable_map_.at(child).second)
            && Id({running_count_variable_map_.at(node).first, completed_variable_map_.at(child).first}), IntermediatePrime(node))));
        solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Failure(child) 
            && inc_failure_expr 
            && *(completed_variable_map_.at(child).second)
            && Id({failure_count_variable_map_.at(node).first, completed_variable_map_.at(child).first}), IntermediatePrime(node))));
    }
    solver_.add(z3::forall(Variables(), z3::implies(Intermediate(node) && success_condition, Success(node))));
    solver_.add(z3::forall(Variables(), z3::implies(Intermediate(node) && running_condition, Running(node))));
    solver_.add(z3::forall(Variables(), z3::implies(Intermediate(node) && failure_condition, Failure(node))));


    // FIXME
    for (auto child : node->GetChildren()) {
        CreateRules(child);
    }
}

void LinearEncoding::CreateRules(std::shared_ptr<arcade::ir::ActionNode> node) {
    CreateRules(node->GetCfa());
    solver_.add(z3::forall(Variables(), z3::implies(Tick(node), Location(node->GetCfa()->GetInitialLocation()))));

    if (node->GetCfa()->GetSuccessLocation().has_value()) {
        solver_.add(z3::forall(Variables(), z3::implies(Location(node->GetCfa()->GetSuccessLocation().value()), Success(node))));
    } else {
        solver_.add(z3::forall(Variables(), z3::implies(false, Success(node))));
    }
    if (node->GetCfa()->GetRunningLocation().has_value()) {
        solver_.add(z3::forall(Variables(), z3::implies(Location(node->GetCfa()->GetRunningLocation().value()), Running(node))));
    } else {
        solver_.add(z3::forall(Variables(), z3::implies(false, Running(node))));
    }
    if (node->GetCfa()->GetFailureLocation().has_value()) {
        solver_.add(z3::forall(Variables(), z3::implies(Location(node->GetCfa()->GetFailureLocation().value()), Failure(node))));
    } else {
        solver_.add(z3::forall(Variables(), z3::implies(false, Failure(node))));
    }
}

void LinearEncoding::CreateRules(std::shared_ptr<arcade::ir::ConditionNode> node) {
    CreateRules(node->GetCfa());
    solver_.add(z3::forall(Variables(), z3::implies(Tick(node), Location(node->GetCfa()->GetInitialLocation()))));

    if (node->GetCfa()->GetSuccessLocation().has_value()) {
        solver_.add(z3::forall(Variables(), z3::implies(Location(node->GetCfa()->GetSuccessLocation().value()), Success(node))));
    } else {
        solver_.add(z3::forall(Variables(), z3::implies(false, Success(node))));
    }

        solver_.add(z3::forall(Variables(), z3::implies(false, Running(node))));
    
    if (node->GetCfa()->GetFailureLocation().has_value()) {
        solver_.add(z3::forall(Variables(), z3::implies(Location(node->GetCfa()->GetFailureLocation().value()), Failure(node))));
    } else {
        solver_.add(z3::forall(Variables(), z3::implies(false, Failure(node))));
    }

}

void LinearEncoding::CreateRules(std::shared_ptr<arcade::ir::Cfa> cfa) {
    for (auto location : cfa->GetLocations()) {
        for (auto transition : location->GetTransitions()) {
            auto assert_statement = std::dynamic_pointer_cast<arcade::ir::AssertStatement>(transition->GetStatement());
            if (assert_statement) {
                solver_.add(z3::forall(Variables(), z3::implies(Location(location), Encode(assert_statement))));
                solver_.add(z3::forall(Variables(), z3::implies(Location(location), Location(transition->ToLocation().lock()))));
            }
            auto assume_statement = std::dynamic_pointer_cast<arcade::ir::AssumeStatement>(transition->GetStatement());
            auto return_statement = std::dynamic_pointer_cast<arcade::ir::ReturnStatement>(transition->GetStatement());
            if (assume_statement || return_statement) {
                solver_.add(z3::forall(Variables(), z3::implies(Location(location) && Encode(transition->GetStatement()), Location(transition->ToLocation().lock())))); 
            }
            auto bool_assign_statement = std::dynamic_pointer_cast<arcade::ir::BooleanAssignment>(transition->GetStatement());
            auto int_assign_statement = std::dynamic_pointer_cast<arcade::ir::IntegerAssignment>(transition->GetStatement());
            if (bool_assign_statement || int_assign_statement) {
                z3::expr id(context_);
                if (bool_assign_statement) {
                    id = Id({boolean_variable_map_.at(bool_assign_statement->Variable()).first});
                }
                if (int_assign_statement) {
                    id = Id({integer_variable_map_.at(int_assign_statement->Variable()).first});
                }

                solver_.add(z3::forall(VariablesAndPrimed(), z3::implies(Location(location) && Encode(transition->GetStatement()) && id, LocationPrime(transition->ToLocation().lock())))); 
            }
            // TODO: completeness check
        }
    }
}

z3::expr_vector LinearEncoding::Variables() {
    auto vec = z3::expr_vector(context_);
    for (auto &[var, var_prime] : variables_) {
        vec.push_back(*var);
    }
    return vec;
}

z3::expr_vector LinearEncoding::VariablesPrimed() {
    auto vec = z3::expr_vector(context_);
    for (auto &[var, var_prime] : variables_) {
        vec.push_back(*var_prime);
    }
    return vec;
}

z3::expr_vector LinearEncoding::VariablesAndPrimed() {
    auto vec = z3::expr_vector(context_);
    for (auto &[var, var_prime] : variables_) {
        vec.push_back(*var);
    }
    for (auto &[var, var_prime] : variables_) {
        vec.push_back(*var_prime);
    }
    return vec;
}

z3::expr LinearEncoding::Tick(std::shared_ptr<arcade::ir::Node> node) {
    return (*tick_predicate_map_[node])(Variables());
}

z3::expr LinearEncoding::TickPrime(std::shared_ptr<arcade::ir::Node> node) {
    return (*tick_predicate_map_[node])(VariablesPrimed());
}

z3::expr LinearEncoding::Success(std::shared_ptr<arcade::ir::Node> node) {
    return (*success_predicate_map_[node])(Variables());
}

z3::expr LinearEncoding::SuccessPrime(std::shared_ptr<arcade::ir::Node> node) {
    return (*success_predicate_map_[node])(VariablesPrimed());
}

z3::expr LinearEncoding::Running(std::shared_ptr<arcade::ir::Node> node) {
    return (*running_predicate_map_[node])(Variables());
}

z3::expr LinearEncoding::RunningPrime(std::shared_ptr<arcade::ir::Node> node) {
    return (*running_predicate_map_[node])(VariablesPrimed());
}

z3::expr LinearEncoding::Failure(std::shared_ptr<arcade::ir::Node> node) {
    return (*failure_predicate_map_[node])(Variables());
}

z3::expr LinearEncoding::FailurePrime(std::shared_ptr<arcade::ir::Node> node) {
    return (*failure_predicate_map_[node])(VariablesPrimed());
}

z3::expr LinearEncoding::Location(std::shared_ptr<arcade::ir::Location> location) {
    return (*location_predicate_map_[location])(Variables());
}

z3::expr LinearEncoding::LocationPrime(std::shared_ptr<arcade::ir::Location> location) {
    return (*location_predicate_map_[location])(VariablesPrimed());
}

z3::expr LinearEncoding::Intermediate(std::shared_ptr<arcade::ir::Node> node) {
    return (*intermediate_predicate_map_[node])(Variables());
}

z3::expr LinearEncoding::IntermediatePrime(std::shared_ptr<arcade::ir::Node> node) {
    return (*intermediate_predicate_map_[node])(VariablesPrimed());
}




// encoding statements
z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::Statement> statement) {
    auto integer_assignment = std::dynamic_pointer_cast<arcade::ir::IntegerAssignment>(statement);
    if (integer_assignment) {
        return Encode(integer_assignment);
    }
    auto boolean_assignment = std::dynamic_pointer_cast<arcade::ir::BooleanAssignment>(statement);
    if (boolean_assignment) {
        return Encode(boolean_assignment);
    }
    auto assert_statement = std::dynamic_pointer_cast<arcade::ir::AssertStatement>(statement);
    if (assert_statement) {
        return Encode(assert_statement);
    }
    auto assume_statement = std::dynamic_pointer_cast<arcade::ir::AssumeStatement>(statement);
    if (assume_statement) {
        return Encode(assume_statement);
    }
    auto return_statement = std::dynamic_pointer_cast<arcade::ir::ReturnStatement>(statement);
    if (return_statement) {
        return Encode(return_statement);
    }
    // TODO check of completeness
    throw std::logic_error("unkown statement");
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::IntegerAssignment> statement) {
    auto variable = *(integer_variable_map_.at(statement->Variable()).second);
    auto expression = Encode(statement->Expression());
    return variable == expression;
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::BooleanAssignment> statement) {
    auto variable = *(boolean_variable_map_.at(statement->Variable()).second);
    auto expression = Encode(statement->Expression());
    return variable == expression;
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::AssertStatement> statement) {
    return Encode(statement->GetCondition());
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::AssumeStatement> statement) {
    return Encode(statement->GetCondition());
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::ReturnStatement> statement) {
    return context_.bool_val(true);
    // TODO remove skip statement?
}


// encoding expressions
z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::Expression> expression) {
    auto unary_arith_expression = std::dynamic_pointer_cast<arcade::ir::UnaryArithmeticOperation>(expression);
    if (unary_arith_expression) {
        return Encode(unary_arith_expression);
    }
    auto binary_arith_expression = std::dynamic_pointer_cast<arcade::ir::BinaryArithmeticOperation>(expression);
    if (binary_arith_expression) {
        return Encode(binary_arith_expression);
    }
    auto unary_bool_expression = std::dynamic_pointer_cast<arcade::ir::UnaryBooleanOperation>(expression);
    if (unary_bool_expression) {
        return Encode(unary_bool_expression);
    }
    auto binary_bool_expression = std::dynamic_pointer_cast<arcade::ir::BinaryBooleanOperation>(expression);
    if (binary_bool_expression) {
        return Encode(binary_bool_expression);
    }
    auto binary_arith_comp_expression = std::dynamic_pointer_cast<arcade::ir::BinaryArithmeticComparisionOperation>(expression);
    if (binary_arith_comp_expression) {
        return Encode(binary_arith_comp_expression);
    }
    auto bool_lit_expression = std::dynamic_pointer_cast<arcade::ir::BooleanLiteral>(expression);
    if (bool_lit_expression) {
        return Encode(bool_lit_expression);
    }
    auto arith_lit_expression = std::dynamic_pointer_cast<arcade::ir::ArithmeticLiteral>(expression);
    if (arith_lit_expression) {
        return Encode(arith_lit_expression);
    }
    auto arith_variable_expression = std::dynamic_pointer_cast<arcade::ir::IntegerVariable>(expression);
    if (arith_variable_expression) {
        return Encode(arith_variable_expression);
    }
    auto bool_variable_expression = std::dynamic_pointer_cast<arcade::ir::BooleanVariable>(expression);
    if (bool_variable_expression) {
        return Encode(bool_variable_expression);
    }
    // TODO check of completeness
    throw std::logic_error("unkown expression");
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::UnaryArithmeticOperation> expression) {
    auto op = Encode(expression->Operand());
    switch (expression->Operator())
    {
    case arcade::ir::UnaryArithmeticOperator::kMinus:
        return -op;
    default:
        // TODO throw exception
        throw std::logic_error("unkown operator");
    }
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::BinaryArithmeticOperation> expression) {
    auto lhs = Encode(expression->LhsOperand());
    auto rhs = Encode(expression->RhsOperand());
    switch (expression->Operator())
    {
    case arcade::ir::BinaryArithmeticOperator::kAddition:
        return lhs + rhs;
    case arcade::ir::BinaryArithmeticOperator::kDivision:
        return lhs / rhs;  
    case arcade::ir::BinaryArithmeticOperator::kMultiplication:
        return lhs * rhs; 
    case arcade::ir::BinaryArithmeticOperator::kSubstraction:
        return lhs - rhs;   
    case arcade::ir::BinaryArithmeticOperator::kModulo:
        return lhs % rhs;
    default:
        // TODO throw exception
        throw std::logic_error("unkown operator");
    }
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::UnaryBooleanOperation> expression) {
    auto op = Encode(expression->Operand());
    switch (expression->Operator())
    {
    case arcade::ir::UnaryBooleanOperator::kNegation :
        return !op;
    default:
        // TODO throw exception
        throw std::logic_error("unkown operator");
    }    
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::BinaryBooleanOperation> expression) {
    auto lhs = Encode(expression->LhsOperand());
    auto rhs = Encode(expression->RhsOperand());
    switch (expression->Operator())
    {
    case arcade::ir::BinaryBooleanOperator::kConjunction:
        return lhs && rhs;
    case arcade::ir::BinaryBooleanOperator::kDisjunction:
        return lhs || rhs;  
    case arcade::ir::BinaryBooleanOperator::kExclusiveOr:
        return lhs ^ rhs; 
    case arcade::ir::BinaryBooleanOperator::kImplication:
        return z3::implies(lhs, rhs);   
    default:
        // TODO throw exception
        throw std::logic_error("unkown operator");
    }
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::BinaryArithmeticComparisionOperation> expression) {
    auto lhs = Encode(expression->LhsOperand());
    auto rhs = Encode(expression->RhsOperand());
    switch (expression->Operator())
    {
    case arcade::ir::BinaryArithmeticComparisionOperator::kEqual:
        return lhs == rhs;
    case arcade::ir::BinaryArithmeticComparisionOperator::kGreater:
        return lhs > rhs;  
    case arcade::ir::BinaryArithmeticComparisionOperator::kGreaterOrEqual:
        return lhs >= rhs; 
    case arcade::ir::BinaryArithmeticComparisionOperator::kLess:
        return lhs < rhs; 
    case arcade::ir::BinaryArithmeticComparisionOperator::kLessOrEqual:
        return lhs <= rhs; 
    case arcade::ir::BinaryArithmeticComparisionOperator::kUnequal:
        return lhs != rhs;    
    default:
        // TODO throw exception
        throw std::logic_error("unkown operator");
    }
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::BooleanLiteral> expression) {
    return context_.bool_val(expression->Value());
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::ArithmeticLiteral> expression) {
    return context_.int_val(expression->Value());
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::IntegerVariable> expression) {
    return *(integer_variable_map_.at(expression).first);
}

z3::expr LinearEncoding::Encode(std::shared_ptr<arcade::ir::BooleanVariable> expression) {
    return *(boolean_variable_map_.at(expression).first);
}

void LinearEncoding::CreateLoop() {
    solver_.add(z3::forall(Variables(), z3::implies(Success(behavior_tree_), Tick(behavior_tree_))));
    solver_.add(z3::forall(Variables(), z3::implies(Running(behavior_tree_), Tick(behavior_tree_))));
    solver_.add(z3::forall(Variables(), z3::implies(Failure(behavior_tree_), Tick(behavior_tree_))));
}

void LinearEncoding::CreateInitialization() {
    /*
    must be called after variable creation (TODO: enforce)
    */
   auto init = z3::mk_and(initialization_);
   solver_.add(z3::forall(Variables(), z3::implies(init, Tick(behavior_tree_))));
}


z3::expr LinearEncoding::Id(std::vector<std::shared_ptr<z3::expr>> except) {
    auto vec = z3::expr_vector(context_);
   
    for (auto [var, var_prime] : variables_) {
        if (nondeterministic_.at(var)) {
            continue;
        }

        bool skip = false;
        for (auto ex : except) {
            if (ex == var) {
                skip = true;
            }
        }
        if (skip) {
            continue;
        }
        vec.push_back(*var == *var_prime);
    }
    return z3::mk_and(vec);
}

}