#ifndef IR_EXPRESSION
#define IR_EXPRESSION

#include <memory>
#include <ostream>

#include "visitor.h"

namespace arcade::ir {

class Expression {
public:
    virtual ~Expression() = default;

    virtual void Print(std::ostream &out) const = 0;

    virtual void Accept(ExpressionVisitor &visitor) = 0;
private:
};

class ArithmeticExpression : public Expression {
public:
    virtual ~ArithmeticExpression() = default;

    virtual void Accept(ExpressionVisitor &visitor) = 0;
private:
};

class BooleanExpression : public Expression {
public:
    virtual ~BooleanExpression() = default;

    virtual void Accept(ExpressionVisitor &visitor) = 0;
private:
};

template<typename Operator_t, typename Domain>
class UnaryOperation {
public:
    UnaryOperation(const Operator_t &the_operator, const Domain &operand);

    Operator_t Operator() const;
    Domain Operand() const;
private:
    Operator_t operator_;
    Domain operand_;
};

template<typename Operator_t, typename Domain>
class BinaryOperation {
public:
    BinaryOperation(const Operator_t &the_operator, const Domain &lhs_operand, const Domain &rhs_operand);

    Operator_t Operator() const;
    Domain LhsOperand() const;
    Domain RhsOperand() const;
private:
    Operator_t operator_;
    Domain lhs_operand_;
    Domain rhs_operand_; 
};

enum class UnaryArithmeticOperator {
    kMinus
};

enum class BinaryArithmeticOperator {
    kAddition, kSubstraction, kMultiplication, kDivision, kModulo
};

enum class UnaryBooleanOperator {
    kNegation
};

enum class BinaryBooleanOperator {
    kConjunction, kDisjunction, kImplication, kExclusiveOr
};

enum class BinaryArithmeticComparisionOperator {
    kEqual, kUnequal, kLess, kLessOrEqual, kGreater, kGreaterOrEqual
};

class UnaryArithmeticOperation : public ArithmeticExpression, public UnaryOperation<UnaryArithmeticOperator, std::shared_ptr<ArithmeticExpression>> {
public:
    UnaryArithmeticOperation(const UnaryArithmeticOperator &the_operator, std::shared_ptr<ArithmeticExpression> operand);


    virtual void Accept(ExpressionVisitor &visitor);
    void Print(std::ostream &out) const;
private:
};

class BinaryArithmeticOperation : public ArithmeticExpression, public BinaryOperation<BinaryArithmeticOperator, std::shared_ptr<ArithmeticExpression>> {
public:
    BinaryArithmeticOperation(const BinaryArithmeticOperator &the_operator, std::shared_ptr<ArithmeticExpression> lhs_operand, std::shared_ptr<ArithmeticExpression> rhs_operand);

    virtual void Accept(ExpressionVisitor &visitor);
    void Print(std::ostream &out) const;
private:
};

class UnaryBooleanOperation : public BooleanExpression, public UnaryOperation<UnaryBooleanOperator, std::shared_ptr<BooleanExpression>> {
public:
    UnaryBooleanOperation(const UnaryBooleanOperator &the_operator, std::shared_ptr<BooleanExpression> operand);

    virtual void Accept(ExpressionVisitor &visitor);
    void Print(std::ostream &out) const;
private:
};

class BinaryBooleanOperation : public BooleanExpression, public BinaryOperation<BinaryBooleanOperator, std::shared_ptr<BooleanExpression>> {
public:
    BinaryBooleanOperation(const BinaryBooleanOperator &the_operator, std::shared_ptr<BooleanExpression> lhs_operand, std::shared_ptr<BooleanExpression> rhs_operand);

    virtual void Accept(ExpressionVisitor &visitor);
    void Print(std::ostream &out) const;
private:
};

class BinaryArithmeticComparisionOperation : public BooleanExpression, public BinaryOperation<BinaryArithmeticComparisionOperator, std::shared_ptr<ArithmeticExpression>> {
public:
    BinaryArithmeticComparisionOperation(const BinaryArithmeticComparisionOperator &the_operator, std::shared_ptr<ArithmeticExpression> lhs_operand, std::shared_ptr<ArithmeticExpression> rhs_operand);

    virtual void Accept(ExpressionVisitor &visitor);
    void Print(std::ostream &out) const;
private:
};


class BooleanLiteral : public BooleanExpression {
public:
    BooleanLiteral(bool value);


    virtual void Accept(ExpressionVisitor &visitor);
    void Print(std::ostream &out) const;

    bool Value() const;
private:
    bool value_;
};

class ArithmeticLiteral : public ArithmeticExpression {
public:
    ArithmeticLiteral(int value);

    virtual void Accept(ExpressionVisitor &visitor) ;
    void Print(std::ostream &out) const;

    int Value() const;
private:
    int value_;
};

class BooleanExpressionHandle {
public:
    BooleanExpressionHandle(std::shared_ptr<BooleanExpression> expression);
    BooleanExpressionHandle(bool value);

    std::shared_ptr<BooleanExpression> Expression() const;
private:
    std::shared_ptr<BooleanExpression> expression_;
};

class ArithmeticExpressionHandle {
public:
    ArithmeticExpressionHandle(std::shared_ptr<ArithmeticExpression> expression);
    ArithmeticExpressionHandle(int value);

    std::shared_ptr<ArithmeticExpression> Expression() const;
private:
    std::shared_ptr<ArithmeticExpression> expression_;
};


ArithmeticExpressionHandle operator-(const ArithmeticExpressionHandle &operand);

ArithmeticExpressionHandle operator+(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
ArithmeticExpressionHandle operator-(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
ArithmeticExpressionHandle operator*(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
ArithmeticExpressionHandle operator/(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
ArithmeticExpressionHandle operator%(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);

BooleanExpressionHandle operator!(const BooleanExpressionHandle &operand);

BooleanExpressionHandle operator&(const BooleanExpressionHandle &lhs, const BooleanExpressionHandle &rhs);
BooleanExpressionHandle operator|(const BooleanExpressionHandle &lhs, const BooleanExpressionHandle &rhs);
BooleanExpressionHandle operator>>(const BooleanExpressionHandle &lhs, const BooleanExpressionHandle &rhs); //imply
BooleanExpressionHandle operator^(const BooleanExpressionHandle &lhs, const BooleanExpressionHandle &rhs); // xor

BooleanExpressionHandle operator==(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
BooleanExpressionHandle operator!=(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
BooleanExpressionHandle operator<(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
BooleanExpressionHandle operator<=(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
BooleanExpressionHandle operator>(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
BooleanExpressionHandle operator>=(const ArithmeticExpressionHandle &lhs, const ArithmeticExpressionHandle &rhs);
} // namespace arcade::ir

#endif // IR_EXPRESSION