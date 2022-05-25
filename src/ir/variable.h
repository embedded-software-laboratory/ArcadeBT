#ifndef IR_VARIABLE
#define IR_VARIABLE

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "expression.h"
#include "visitor.h"


namespace arcade::ir {

// forward declaration
class Cfa;

enum class AccessType {
    kWrite,
    kRead
};

class Variable {
public:
    Variable(const std::string &name, const AccessType &access_type);
    virtual ~Variable() = default;

    std::string Name() const; 
    AccessType GetAccessType() const;
private:
    std::string name_;
    AccessType access_type_;
};

class BooleanVariable : public BooleanExpression, public Variable {
public:
    BooleanVariable(const std::string &name, const bool& initial_value, const AccessType &access_type);

    virtual void Accept(ExpressionVisitor &visitor);
    void Print(std::ostream &out) const;

    bool GetInitialValue() const;
private:
    bool initial_value_;
};

class IntegerVariable : public ArithmeticExpression, public Variable {
public:
    IntegerVariable(const std::string &name, const int& initial_value, const AccessType &access_type);

    virtual void Accept(ExpressionVisitor &visitor) ;
    void Print(std::ostream &out) const;

    int GetInitialValue() const;
private:
    int initial_value_;
};

class VariableManager {
public:
    BooleanExpressionHandle AddGlobalBooleanVariable(const std::string &name, const bool &initial_value, const AccessType &access_type);
    ArithmeticExpressionHandle AddGlobalIntegerVariable(const std::string &name, const int &initial_value, const AccessType &access_type);
    BooleanExpressionHandle AddLocalBooleanVariable(const std::string &name, const bool &initial_value, const AccessType &access_type, std::shared_ptr<Cfa> cfa);
    ArithmeticExpressionHandle AddLocalIntegerVariable(const std::string &name, const int &initial_value, const AccessType &access_type, std::shared_ptr<Cfa> cfa);

    std::vector<std::shared_ptr<BooleanVariable>> GetGlobalBooleanVariables();
    std::vector<std::shared_ptr<IntegerVariable>> GetGlobalIntegerVariables();
    std::vector<std::shared_ptr<BooleanVariable>> GetLocalBooleanVariables(std::shared_ptr<Cfa> cfa);
    std::vector<std::shared_ptr<IntegerVariable>> GetLocalIntegerVariables(std::shared_ptr<Cfa> cfa);

    bool IsGlobal(std::shared_ptr<BooleanVariable> variable) const;
    bool IsGlobal(std::shared_ptr<IntegerVariable> variable) const;

    std::shared_ptr<Cfa> GetCfa(std::shared_ptr<BooleanVariable> variable);
    std::shared_ptr<Cfa> GetCfa(std::shared_ptr<IntegerVariable> variable);

private:
    std::vector<std::shared_ptr<BooleanVariable>> global_boolean_variables_;
    std::vector<std::shared_ptr<IntegerVariable>> global_integer_variables_;

    std::map<std::shared_ptr<Cfa>, std::vector<std::shared_ptr<BooleanVariable>>> local_boolean_variables_;
    std::map<std::shared_ptr<Cfa>, std::vector<std::shared_ptr<IntegerVariable>>> local_integer_variables_;
};

} // namespace arcade::ir

#endif // IR_VARIABLE