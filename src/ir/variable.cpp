#include "variable.h"

#include <sstream>

namespace arcade::ir {

// Variable
Variable::Variable(const std::string &name, const AccessType &access_type)
    : name_(name), access_type_(access_type) {
}

std::string Variable::Name() const {
    return name_;
}

AccessType Variable::GetAccessType() const {
    return access_type_;
}


// BooleanVariable
BooleanVariable::BooleanVariable(const std::string &name, const bool& initial_value, const AccessType &access_type)
    : BooleanExpression(), Variable(name, access_type), initial_value_(initial_value) {
}

void BooleanVariable::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void BooleanVariable::Print(std::ostream &out) const {
    out << "BVar[" << Name() << ", " << GetInitialValue() << ", " << (GetAccessType() == AccessType::kRead ? "nondeterministic" : "deterministic") << "]";
}

bool BooleanVariable::GetInitialValue() const {
    return initial_value_;
}


// IntegerVariable
IntegerVariable::IntegerVariable(const std::string &name, const int& initial_value, const AccessType &access_type)
    : ArithmeticExpression(), Variable(name, access_type), initial_value_(initial_value) {
}

void IntegerVariable::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void IntegerVariable::Print(std::ostream &out) const {
    out << "AVar[" << Name() << ", " << GetInitialValue() << ", " << (GetAccessType() == AccessType::kRead ? "nondeterministic" : "deterministic") << "]";
}

int IntegerVariable::GetInitialValue() const {
    return initial_value_;
}


// VariableManager
BooleanExpressionHandle VariableManager::AddGlobalBooleanVariable(const std::string &name, const bool &initial_value, const AccessType &access_type) {
    auto variable = std::make_shared<BooleanVariable>(name, initial_value, access_type);
    global_boolean_variables_.push_back(variable);
    return BooleanExpressionHandle(variable);
}

ArithmeticExpressionHandle VariableManager::AddGlobalIntegerVariable(const std::string &name, const int &initial_value, const AccessType &access_type) {
    auto variable = std::make_shared<IntegerVariable>(name, initial_value, access_type);
    global_integer_variables_.push_back(variable);
    return ArithmeticExpressionHandle(variable);
}

BooleanExpressionHandle VariableManager::AddLocalBooleanVariable(const std::string &name, const bool &initial_value, const AccessType &access_type, std::shared_ptr<Cfa> cfa) {
    auto variable = std::make_shared<BooleanVariable>(name, initial_value, access_type);
    local_boolean_variables_[cfa].push_back(variable);
    return BooleanExpressionHandle(variable);
}
ArithmeticExpressionHandle VariableManager::AddLocalIntegerVariable(const std::string &name, const int &initial_value, const AccessType &access_type, std::shared_ptr<Cfa> cfa) {
    auto variable = std::make_shared<IntegerVariable>(name, initial_value, access_type);
    local_integer_variables_[cfa].push_back(variable);
    return ArithmeticExpressionHandle(variable);
}

std::vector<std::shared_ptr<BooleanVariable>> VariableManager::GetGlobalBooleanVariables() {
    return global_boolean_variables_;
}

std::vector<std::shared_ptr<IntegerVariable>> VariableManager::GetGlobalIntegerVariables() {
    return global_integer_variables_;
}

std::vector<std::shared_ptr<BooleanVariable>> VariableManager::GetLocalBooleanVariables(std::shared_ptr<Cfa> cfa) {
    return local_boolean_variables_[cfa];
}

std::vector<std::shared_ptr<IntegerVariable>> VariableManager::GetLocalIntegerVariables(std::shared_ptr<Cfa> cfa) {
    return local_integer_variables_[cfa];
}

bool VariableManager::IsGlobal(std::shared_ptr<BooleanVariable> variable) const {
    for (const auto var : global_boolean_variables_) {
        if (variable == var) {
            return true;
        }
    }
    return false;
}

bool VariableManager::IsGlobal(std::shared_ptr<IntegerVariable> variable) const {
    for (const auto var : global_integer_variables_) {
        if (variable == var) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Cfa> VariableManager::GetCfa(std::shared_ptr<BooleanVariable> variable) {
    if (IsGlobal(variable)) {
        std::stringstream ss;
        variable->Print(ss);
        throw std::logic_error("variable \"" + ss.str() + "\" is not a local variable");
    }

    for (auto [cfa, variables] : local_boolean_variables_) {
        for (auto var : variables) {
            if (variable == var) {
                return cfa;
            }
        }
    }

    return nullptr;
}

std::shared_ptr<Cfa> VariableManager::GetCfa(std::shared_ptr<IntegerVariable> variable) {
    if (IsGlobal(variable)) {
        std::stringstream ss;
        variable->Print(ss);
        throw std::logic_error("variable \"" + ss.str() + "\" is not a local variable");
    }

    for (auto [cfa, variables] : local_integer_variables_) {
        for (auto var : variables) {
            if (variable == var) {
                return cfa;
            }
        }
    }

    return nullptr;
}

} // namespace arcade::ir