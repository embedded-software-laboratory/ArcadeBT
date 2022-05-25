#include "variable_factory.h"

#include "../../ir/bt.h"
#include "../variable.h"
#include "encoding.h"

namespace arcade::analysis::linear
{

// VariableFactory
VariableFactory::VariableFactory(std::shared_ptr<Encoding> encoding)
    : encoding_(encoding) {
}

void VariableFactory::Visit(arcade::ir::SequenceNode *node) {
    if (node->GetMemory()) {
        auto variable = Variable::CreateIntegerVariable(encoding_->context_, "memory_" + std::to_string(node->GetId()));
        encoding_->memory_variable_map.insert({node->shared_from_this(), variable});
    }
}

void VariableFactory::Visit(arcade::ir::SelectorNode *node) {
    if (node->GetMemory()) {
        auto variable = Variable::CreateIntegerVariable(encoding_->context_, "memory_" + std::to_string(node->GetId()));
        encoding_->memory_variable_map.insert({node->shared_from_this(), variable});
    }
}

void VariableFactory::Visit(arcade::ir::ParallelNode *node) {
    auto count_success_variable =  Variable::CreateIntegerVariable(encoding_->context_, "count_success" + std::to_string(node->GetId()));
    encoding_->count_success_variable_map.insert({node->shared_from_this(), count_success_variable});

    auto count_running_variable =  Variable::CreateIntegerVariable(encoding_->context_, "count_running" + std::to_string(node->GetId()));
    encoding_->count_running_variable_map.insert({node->shared_from_this(), count_running_variable});

    auto count_failure_variable =  Variable::CreateIntegerVariable(encoding_->context_, "count_failure" + std::to_string(node->GetId()));
    encoding_->count_failure_variable_map.insert({node->shared_from_this(), count_failure_variable});

    for (auto child : node->GetChildren()) {
        auto completed_variable =  Variable::CreateBooleanVariable(encoding_->context_, "completed" + std::to_string(node->GetId()));
        encoding_->completed_variable_map.insert({node->shared_from_this(), completed_variable});        
    }
}

void VariableFactory::Visit(arcade::ir::ActionNode *node) {
    CreateLocalVariables(node->GetCfa(), node->GetId());
}

void VariableFactory::Visit(arcade::ir::ConditionNode *node) {
    CreateLocalVariables(node->GetCfa(), node->GetId());
}

void VariableFactory::CreateGlobalVariables() {
    for (auto integer_variable : encoding_->vm_->GetGlobalIntegerVariables()) {
        auto z3_variable = Variable::CreateGlobalIntegerVariable(encoding_->context_, integer_variable->Name());
        encoding_->cfa_variable_map_.insert({integer_variable, z3_variable});
    }

    for (auto boolean_variable : encoding_->vm_->GetGlobalBooleanVariables()) {
        auto z3_variable = Variable::CreateGlobalBooleanVariable(encoding_->context_, boolean_variable->Name());
        encoding_->cfa_variable_map_.insert({boolean_variable, z3_variable});
    }
}

void VariableFactory::CreateLocalVariables(std::shared_ptr<arcade::ir::Cfa> cfa, unsigned node_id) {
    for (auto integer_variable : encoding_->vm_->GetLocalIntegerVariables(cfa)) {
        auto z3_variable = Variable::CreateLocalIntegerVariable(encoding_->context_, integer_variable->Name(), node_id);
        encoding_->cfa_variable_map_.insert({integer_variable, z3_variable});
    }

    for (auto boolean_variable : encoding_->vm_->GetLocalBooleanVariables(cfa)) {
        auto z3_variable = Variable::CreateLocalBooleanVariable(encoding_->context_, boolean_variable->Name(), node_id);
        encoding_->cfa_variable_map_.insert({boolean_variable, z3_variable});
    }
}

} // namespace arcade::analysis::linear