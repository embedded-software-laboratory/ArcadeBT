#include "statement.h"

namespace arcade::ir {

// Assignment 
template<typename VariableType, typename ExpressionType>
Assignment<VariableType, ExpressionType>::Assignment(const VariableType &variable, const ExpressionType &expression)
    : variable_(variable), expression_(expression) {
}

template<typename VariableType, typename ExpressionType>
VariableType Assignment<VariableType, ExpressionType>::Variable() const {
    return variable_;
}

template<typename VariableType, typename ExpressionType>
ExpressionType Assignment<VariableType, ExpressionType>::Expression() const {
    return expression_;
}

template<typename VariableType, typename ExpressionType>
void Assignment<VariableType, ExpressionType>::Print(std::ostream &out) const {
    out << "asign: ";
    variable_->Print(out);
    out << " := ";
    expression_->Print(out);
}

template class Assignment<std::shared_ptr<BooleanVariable>, std::shared_ptr<BooleanExpression>>;
template class Assignment<std::shared_ptr<IntegerVariable>, std::shared_ptr<ArithmeticExpression>>;


// BooleanAssignment
BooleanAssignment:: BooleanAssignment(std::shared_ptr<BooleanVariable> variable, std::shared_ptr<BooleanExpression> expression)
    : Assignment<std::shared_ptr<BooleanVariable>, std::shared_ptr<BooleanExpression>>(variable, expression) {
}


// IntegerAssignment
IntegerAssignment::IntegerAssignment(std::shared_ptr<IntegerVariable> variable, std::shared_ptr<ArithmeticExpression> expression)
    : Assignment<std::shared_ptr<IntegerVariable>, std::shared_ptr<ArithmeticExpression>>(variable, expression) {
}


// AssertStatement
AssertStatement::AssertStatement(std::shared_ptr<BooleanExpression> condition)
    : Statement(), condition_(condition) {
}

void AssertStatement::Print(std::ostream &out) const {
    out << "assert: ";
    condition_->Print(out);
}

std::shared_ptr<BooleanExpression> AssertStatement::GetCondition() {
    return condition_;
}


// AssumeStatement
AssumeStatement::AssumeStatement(std::shared_ptr<BooleanExpression> condition)
    : Statement(), condition_(condition) {
}

void AssumeStatement::Print(std::ostream &out) const {
    out << "assume: ";
    condition_->Print(out); 
}

std::shared_ptr<BooleanExpression> AssumeStatement::GetCondition() {
    return condition_;
}

const std::shared_ptr<BooleanExpression> AssumeStatement::GetCondition() const {
    return condition_;
}


// BranchStatement
BranchStatement::BranchStatement(std::shared_ptr<BooleanExpression> condition, bool primary_branch, BranchType branch_type, std::weak_ptr<Transition> other_branch)
    : AssumeStatement(condition), primary_branch_(primary_branch), branch_type_(branch_type), other_branch_(other_branch) {
}

void BranchStatement::Print(std::ostream &out) const {
    out << "branch  (primary: " << primary_branch_ << ", type: " << ((branch_type_ == BranchType::kIf) ? "if" : "while") << "): ";
    GetCondition()->Print(out);
}

bool BranchStatement::IsPrimaryBanch() {
    return primary_branch_;
}

BranchType BranchStatement::GetBranchType() {
    return branch_type_;
} 

void BranchStatement::SetOtherBranch(std::weak_ptr<Transition> other_branch) {
    other_branch_ = other_branch;
}

std::shared_ptr<Transition> BranchStatement::GetOtherBranch() {
    return other_branch_.lock();
}


// ReturnStatement
ReturnStatement::ReturnStatement(const ReturnValue &return_value)
    : return_value_(return_value) {
}

void ReturnStatement::Print(std::ostream &out) const {
    out << "return: ";
    switch (return_value_)
    {
    case ReturnValue::kSuccess:
        out << "SUCCESS";
        break;
    case ReturnValue::kRunning:
        out << "RUNNING";
        break;
    case ReturnValue::kFailure:
        out << "FAILURE";
        break;

    default:
        throw std::logic_error("unknown return type");
        break;
    }  
}

ReturnValue ReturnStatement::GetReturnValue() const {
    return return_value_;
}

} // namespace arcade::ir