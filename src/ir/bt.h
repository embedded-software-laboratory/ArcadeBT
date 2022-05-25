#ifndef IR_BEHAVIOR_TREE
#define IR_BEHAVIOR_TREE

#include <memory>
#include <vector>

#include "cfa.h"
#include "visitor.h"

namespace arcade::ir {

class Node {
public:
    Node();
    virtual ~Node() = default;

    virtual void Print(std::ostream &out) const = 0;
    virtual void Accept(NodeVisitor &visitor) = 0;

    int GetId() const;
private:
    static int next_id_;
    int id_;
};

class CompositionalNode : public Node {
public:
    CompositionalNode(std::initializer_list<std::shared_ptr<Node>> children);

    virtual void Accept(NodeVisitor &visitor) = 0;

    std::vector<std::shared_ptr<Node>> GetChildren();
    const std::vector<std::shared_ptr<Node>> GetChildren() const;
private:
    std::vector<std::shared_ptr<Node>> children_;
};

class SequenceNode : public CompositionalNode, public std::enable_shared_from_this<SequenceNode> {
public:
    SequenceNode(bool memory, std::initializer_list<std::shared_ptr<Node>> children);

    void Print(std::ostream &out) const;
    virtual void Accept(NodeVisitor &visitor);

    bool GetMemory() const;
private:
    bool memory_;
};

class SelectorNode : public CompositionalNode, public std::enable_shared_from_this<SelectorNode> {
public:
    SelectorNode(bool memory, std::initializer_list<std::shared_ptr<Node>> children);

    void Print(std::ostream &out) const;
    virtual void Accept(NodeVisitor &visitor);

    bool GetMemory() const;
private:
    bool memory_;
};

class ParallelNode : public CompositionalNode, public std::enable_shared_from_this<ParallelNode>  {
public:
    ParallelNode(int threshold, std::initializer_list<std::shared_ptr<Node>> children);

    void Print(std::ostream &out) const;
    virtual void Accept(NodeVisitor &visitor);

    int GetThreshold() const;
private:
    int threshold_;
};

class LeafNode : public Node {
public:
    LeafNode(std::shared_ptr<Cfa> cfa);

    virtual void Accept(NodeVisitor &visitor) = 0;

    std::shared_ptr<Cfa> GetCfa();
    const std::shared_ptr<Cfa> GetCfa() const;
private:
    std::shared_ptr<Cfa> cfa_;
};

class ActionNode : public LeafNode, public std::enable_shared_from_this<ActionNode>  {
public:
    ActionNode(std::shared_ptr<Cfa> cfa);

    void Print(std::ostream &out) const;
    virtual void Accept(NodeVisitor &visitor);
private:
};

class ConditionNode : public LeafNode, public std::enable_shared_from_this<ConditionNode> {
public:
    ConditionNode(std::shared_ptr<Cfa> cfa);

    void Print(std::ostream &out) const;
    virtual void Accept(NodeVisitor &visitor);
private:
};

} // namespace arcade::ir

#endif // IR_BEHAVIOR_TREE