#ifndef IR_STATEMENT
#define IR_STATEMENT

#include "expression.h"
#include "variable.h"

namespace arcade::ir {

class Transition;

class Statement {
public:
    virtual ~Statement() = default;

    virtual void Print(std::ostream &out) const = 0;
private:
};

template<typename VariableType, typename ExpressionType>
class Assignment : public Statement {
public:
    Assignment(const VariableType &variable, const ExpressionType &expression);
    virtual ~Assignment() = default;

    void Print(std::ostream &out) const;

    VariableType Variable() const;
    ExpressionType Expression() const;
private:
    VariableType variable_;
    ExpressionType expression_;
};

class BooleanAssignment : public Assignment<std::shared_ptr<BooleanVariable>, std::shared_ptr<BooleanExpression>> {
public:
    BooleanAssignment(std::shared_ptr<BooleanVariable> variable, std::shared_ptr<BooleanExpression> expression);
private:
};

class IntegerAssignment : public Assignment<std::shared_ptr<IntegerVariable>, std::shared_ptr<ArithmeticExpression>> {
public:
    IntegerAssignment(std::shared_ptr<IntegerVariable> variable, std::shared_ptr<ArithmeticExpression> expression);
private:
};

class AssertStatement : public Statement {
public:
    AssertStatement(std::shared_ptr<BooleanExpression> condition);

    void Print(std::ostream &out) const;

    std::shared_ptr<BooleanExpression> GetCondition();    
private:
    std::shared_ptr<BooleanExpression> condition_;
};

enum class BranchType {
    kIf, kWhile
};

class AssumeStatement : public Statement {
public:
    AssumeStatement(std::shared_ptr<BooleanExpression> condition);

    void Print(std::ostream &out) const;

    std::shared_ptr<BooleanExpression> GetCondition();   
    const std::shared_ptr<BooleanExpression> GetCondition() const; 
private:
    std::shared_ptr<BooleanExpression> condition_;
};

class BranchStatement : public AssumeStatement {
public:
    BranchStatement(std::shared_ptr<BooleanExpression> condition, bool primary_branch, BranchType branch_type, std::weak_ptr<Transition> other_branch);

    void Print(std::ostream &out) const;

    bool IsPrimaryBanch();
    BranchType GetBranchType();    

    void SetOtherBranch(std::weak_ptr<Transition> other_branch);
    std::shared_ptr<Transition> GetOtherBranch();
private:
    bool primary_branch_;
    BranchType branch_type_;
    std::weak_ptr<Transition> other_branch_;
};

enum class ReturnValue {
    kSuccess, kRunning, kFailure
};

class ReturnStatement : public Statement {
public:
    ReturnStatement(const ReturnValue &return_value);

    void Print(std::ostream &out) const;

    ReturnValue GetReturnValue() const;
private:
    ReturnValue return_value_;
};


} // namespace arcade::ir

#endif // IR_STATEMENT