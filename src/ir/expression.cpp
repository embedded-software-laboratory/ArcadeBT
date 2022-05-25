#include "expression.h"

#include <exception>

namespace arcade::ir {

// UnaryOperation
template<typename Operator_t, typename Domain>
UnaryOperation<Operator_t, Domain>::UnaryOperation(const Operator_t &the_operator, const Domain &operand)
    : operator_(the_operator), operand_(operand) {
}

template<typename Operator_t, typename Domain>
Operator_t UnaryOperation<Operator_t, Domain>::Operator() const {
    return operator_;
}

template<typename Operator_t, typename Domain>
Domain UnaryOperation<Operator_t, Domain>::Operand() const {
    return operand_;
}


// BinaryOperation
template<typename Operator_t, typename Domain>
BinaryOperation<Operator_t, Domain>::BinaryOperation(const Operator_t &the_operator, const Domain &lhs_operand, const Domain &rhs_operand)
    : operator_(the_operator), lhs_operand_(lhs_operand), rhs_operand_(rhs_operand) {
}

template<typename Operator_t, typename Domain>
Operator_t BinaryOperation<Operator_t, Domain>::Operator() const {
    return operator_;
}

template<typename Operator_t, typename Domain>
Domain BinaryOperation<Operator_t, Domain>::LhsOperand() const {
    return lhs_operand_;
}

template<typename Operator_t, typename Domain>
Domain BinaryOperation<Operator_t, Domain>::RhsOperand() const {
    return rhs_operand_;
}


// UnaryArithmeticOperation
UnaryArithmeticOperation::UnaryArithmeticOperation(const UnaryArithmeticOperator &the_operator, std::shared_ptr<ArithmeticExpression> operand)
    : ArithmeticExpression(), UnaryOperation<UnaryArithmeticOperator, std::shared_ptr<ArithmeticExpression>>(the_operator, operand) {
}

void UnaryArithmeticOperation::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void UnaryArithmeticOperation::Print(std::ostream &out) const {
    switch (Operator())
    {
    case UnaryArithmeticOperator::kMinus:
        out << "-";
        break;
    default:
        throw std::logic_error("unknown unary arithmetic operator");
        break;
    }

    out << "(";
    Operand()->Print(out);
    out << ")";    
}


// BinaryArithmeticOperation
BinaryArithmeticOperation::BinaryArithmeticOperation(const BinaryArithmeticOperator &the_operator, std::shared_ptr<ArithmeticExpression> lhs_operand, std::shared_ptr<ArithmeticExpression> rhs_operand)
    : ArithmeticExpression(), BinaryOperation<BinaryArithmeticOperator, std::shared_ptr<ArithmeticExpression>>(the_operator, lhs_operand, rhs_operand) {
}

void BinaryArithmeticOperation::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void BinaryArithmeticOperation::Print(std::ostream &out) const {
    out << "(";
    LhsOperand()->Print(out);
    out << ") ";

    switch (Operator())
    {
    case BinaryArithmeticOperator::kAddition:
        out << "+";
        break;
    case BinaryArithmeticOperator::kSubstraction:
        out << "-";
        break;
    case BinaryArithmeticOperator::kMultiplication:
        out << "*";
        break;
    case BinaryArithmeticOperator::kDivision:
        out << "/";
        break;
    case BinaryArithmeticOperator::kModulo:
        out << "%";
        break;
    default:
        throw std::logic_error("unknown binary arithmetic operator");
        break;
    }

    out << " (";
    RhsOperand()->Print(out);
    out << ")";    
}


// UnaryBooleanOperation
UnaryBooleanOperation::UnaryBooleanOperation(const UnaryBooleanOperator &the_operator, std::shared_ptr<BooleanExpression> operand)
    : BooleanExpression(), UnaryOperation<UnaryBooleanOperator, std::shared_ptr<BooleanExpression>>(the_operator, operand) {
}

void UnaryBooleanOperation::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void UnaryBooleanOperation::Print(std::ostream &out) const {
    switch (Operator())
    {
    case UnaryBooleanOperator::kNegation:
        out << "!";
        break;
    default:
        throw std::logic_error("unknown unary boolean operator"); 
        break;
    }

    out << "(";
    Operand()->Print(out);
    out << ")";
}


// BinaryBooleanOperation
BinaryBooleanOperation::BinaryBooleanOperation(const BinaryBooleanOperator &the_operator, std::shared_ptr<BooleanExpression> lhs_operand, std::shared_ptr<BooleanExpression> rhs_operand)
    : BooleanExpression(), BinaryOperation<BinaryBooleanOperator, std::shared_ptr<BooleanExpression>>(the_operator, lhs_operand, rhs_operand) {
}

void BinaryBooleanOperation::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void BinaryBooleanOperation::Print(std::ostream &out) const {
    out << "(";
    LhsOperand()->Print(out);
    out << ") ";

    switch (Operator())
    {
    case BinaryBooleanOperator::kConjunction:
        out << "&";
        break;
    case BinaryBooleanOperator::kDisjunction:
        out << "|";
        break;
    case BinaryBooleanOperator::kImplication:
        out << "->";
        break;
    case BinaryBooleanOperator::kExclusiveOr:
        out << "xor";
        break;
    default:
        throw std::logic_error("unknown binary boolean operator");
        break;
    }

    out << " (";
    RhsOperand()->Print(out);
    out << ")";
}


// BinaryArithmeticComparisionOperation
BinaryArithmeticComparisionOperation::BinaryArithmeticComparisionOperation(const BinaryArithmeticComparisionOperator &the_operator, std::shared_ptr<ArithmeticExpression> lhs_operand, std::shared_ptr<ArithmeticExpression> rhs_operand)
    : BooleanExpression(), BinaryOperation<BinaryArithmeticComparisionOperator, std::shared_ptr<ArithmeticExpression>>(the_operator, lhs_operand, rhs_operand) {
}

void BinaryArithmeticComparisionOperation::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void BinaryArithmeticComparisionOperation::Print(std::ostream &out) const {
    out << "(";
    LhsOperand()->Print(out);
    out << ") ";

    switch (Operator())
    {
    case BinaryArithmeticComparisionOperator::kEqual:
        out << "==";
        break;
    case BinaryArithmeticComparisionOperator::kUnequal:
        out << "!=";
        break;
    case BinaryArithmeticComparisionOperator::kLess:
        out << "<";
        break;
    case BinaryArithmeticComparisionOperator::kLessOrEqual:
        out << "<=";
        break;
    case BinaryArithmeticComparisionOperator::kGreater:
        out << ">";
        break;
    case BinaryArithmeticComparisionOperator::kGreaterOrEqual:
        out << ">=";
        break;
    default:
        throw std::logic_error("unknown binary arithmetic comparision operator");
        break;
    }

    out << " (";
    RhsOperand()->Print(out);
    out << ")";
} 


// BooleanLiteral
BooleanLiteral::BooleanLiteral(bool value)
    : BooleanExpression(), value_{value} {
}

void BooleanLiteral::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void BooleanLiteral::Print(std::ostream &out) const {
    if (value_) {
        out << "true";
    } else {
        out << "false";
    }
}

bool BooleanLiteral::Value() const {
    return value_;
}


// ArithmeticLiteral
ArithmeticLiteral::ArithmeticLiteral(int value)
    : ArithmeticExpression(), value_{value} {
}

void ArithmeticLiteral::Accept(ExpressionVisitor &visitor) {
    visitor.Visit(this);
}

void ArithmeticLiteral::Print(std::ostream &out) const {
    out << value_;
}

int ArithmeticLiteral::Value() const {
    return value_;
}

// BooleanExpressionHandle
BooleanExpressionHandle::BooleanExpressionHandle(std::shared_ptr<BooleanExpression> expression)
    : expression_{expression} {
}

BooleanExpressionHandle::BooleanExpressionHandle(bool value) {
    expression_ = std::make_shared<BooleanLiteral>(value);
}

std::shared_ptr<BooleanExpression> BooleanExpressionHandle::Expression() const {
    return expression_;
}


// ArithmeticExpressionHandle
ArithmeticExpressionHandle::ArithmeticExpressionHandle(std::shared_ptr<ArithmeticExpression> expression)
    : expression_{expression} {
}

ArithmeticExpressionHandle::ArithmeticExpressionHandle(int value) {
    expression_ = std::make_shared<ArithmeticLiteral>(value);
}

std::shared_ptr<ArithmeticExpression> ArithmeticExpressionHandle::Expression() const {
    return expression_;
}


// Operators
ArithmeticExpressionHandle operator-(const ArithmeticExpressionHandle &operand) {
    return ArithmeticExpressionHandle(std::make_shared<UnaryArithmeticOperation>(UnaryArithmeticOperator::kMinus, operand.Expression()));
}

ArithmeticExpressionHandle operator+(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return ArithmeticExpressionHandle(std::make_shared<BinaryArithmeticOperation>(BinaryArithmeticOperator::kAddition, lhs.Expression(), rhs.Expression()));
}

ArithmeticExpressionHandle operator-(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return ArithmeticExpressionHandle(std::make_shared<BinaryArithmeticOperation>(BinaryArithmeticOperator::kSubstraction, lhs.Expression(), rhs.Expression()));
}

ArithmeticExpressionHandle operator*(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return ArithmeticExpressionHandle(std::make_shared<BinaryArithmeticOperation>(BinaryArithmeticOperator::kMultiplication, lhs.Expression(), rhs.Expression()));
}

ArithmeticExpressionHandle operator/(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return ArithmeticExpressionHandle(std::make_shared<BinaryArithmeticOperation>(BinaryArithmeticOperator::kDivision, lhs.Expression(), rhs.Expression()));
}

ArithmeticExpressionHandle operator%(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return ArithmeticExpressionHandle(std::make_shared<BinaryArithmeticOperation>(BinaryArithmeticOperator::kModulo, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator!(const BooleanExpressionHandle &operand) {
    return BooleanExpressionHandle(std::make_shared<UnaryBooleanOperation>(UnaryBooleanOperator::kNegation, operand.Expression()));
}

BooleanExpressionHandle operator&(const BooleanExpressionHandle &lhs, const BooleanExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryBooleanOperation>(BinaryBooleanOperator::kConjunction, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator|(const BooleanExpressionHandle &lhs, const BooleanExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryBooleanOperation>(BinaryBooleanOperator::kDisjunction, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator>>(const BooleanExpressionHandle &lhs, const BooleanExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryBooleanOperation>(BinaryBooleanOperator::kImplication, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator^(const BooleanExpressionHandle &lhs, const BooleanExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryBooleanOperation>(BinaryBooleanOperator::kExclusiveOr, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator==(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryArithmeticComparisionOperation>(BinaryArithmeticComparisionOperator::kEqual, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator!=(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryArithmeticComparisionOperation>(BinaryArithmeticComparisionOperator::kUnequal, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator<(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryArithmeticComparisionOperation>(BinaryArithmeticComparisionOperator::kLess, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator<=(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryArithmeticComparisionOperation>(BinaryArithmeticComparisionOperator::kLessOrEqual, lhs.Expression(), rhs.Expression()));
}

BooleanExpressionHandle operator>(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryArithmeticComparisionOperation>(BinaryArithmeticComparisionOperator::kGreater, lhs.Expression(), rhs.Expression()));
}
BooleanExpressionHandle operator>=(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs) {
    return BooleanExpressionHandle(std::make_shared<BinaryArithmeticComparisionOperation>(BinaryArithmeticComparisionOperator::kGreaterOrEqual, lhs.Expression(), rhs.Expression()));
}

template class UnaryOperation<UnaryArithmeticOperator, std::shared_ptr<ArithmeticExpression>>;
template class BinaryOperation<BinaryArithmeticOperator, std::shared_ptr<ArithmeticExpression>>;
template class UnaryOperation<UnaryBooleanOperator, std::shared_ptr<BooleanExpression>>;
template class BinaryOperation<BinaryBooleanOperator, std::shared_ptr<BooleanExpression>>;
template class BinaryOperation<BinaryArithmeticComparisionOperator, std::shared_ptr<ArithmeticExpression>>;

} // namespace arcade::ir