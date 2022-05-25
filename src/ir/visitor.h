#ifndef IR_VISITOR
#define IR_VISITOR

namespace arcade::ir
{

class UnaryArithmeticOperation;
class BinaryArithmeticOperation;
class UnaryBooleanOperation;
class BinaryBooleanOperation;
class BinaryArithmeticComparisionOperation;
class BooleanLiteral;
class ArithmeticLiteral;
class BooleanVariable;
class IntegerVariable;

class ExpressionVisitor {
public:
    virtual void Visit(UnaryArithmeticOperation *operation) = 0;
    virtual void Visit(BinaryArithmeticOperation *operation) = 0;
    virtual void Visit(UnaryBooleanOperation *operation) = 0;
    virtual void Visit(BinaryBooleanOperation *operation) = 0;
    virtual void Visit(BinaryArithmeticComparisionOperation *operation) = 0;
    virtual void Visit(BooleanLiteral *literal) = 0;
    virtual void Visit(ArithmeticLiteral *literal) = 0;
    virtual void Visit(BooleanVariable *variable) = 0;
    virtual void Visit(IntegerVariable *variable) = 0;
private:
};

class StatementVisitor {
public:

private:
};

class SequenceNode;
class SelectorNode;
class ParallelNode;
class ActionNode;
class ConditionNode;

class NodeVisitor {
public:
    virtual void Visit(SequenceNode *node) = 0;
    virtual void Visit(SelectorNode *node) = 0;
    virtual void Visit(ParallelNode *node) = 0;
    virtual void Visit(ActionNode *node) = 0;
    virtual void Visit(ConditionNode *node) = 0;
private:
};

} // namespace arcade::ir


#endif // IR_VISITOR