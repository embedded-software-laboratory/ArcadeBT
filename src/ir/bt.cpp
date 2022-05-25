#include "bt.h"

namespace arcade::ir {

// Node
Node::Node()
    : id_(next_id_++) {
}

int Node::GetId() const {
    return id_;
}

int Node::next_id_ = 0;


// CompositionalNode
CompositionalNode::CompositionalNode(std::initializer_list<std::shared_ptr<Node>> children)
    : Node(), children_(children) {
}

std::vector<std::shared_ptr<Node>> CompositionalNode::GetChildren() {
    return children_;
}

const std::vector<std::shared_ptr<Node>> CompositionalNode::GetChildren() const {
    return children_;
}


// SequenceNode
SequenceNode::SequenceNode(bool memory, std::initializer_list<std::shared_ptr<Node>> children)
    : CompositionalNode(children), memory_(memory) {
}

void SequenceNode::Print(std::ostream &out) const {
    out << "Seq[id=" << GetId() << "; memory=" << GetMemory() <<"; children=";
    for (auto child : GetChildren()) {
        out << child->GetId() << ",";
    }
    out << "]\n";
    for (auto child : GetChildren()) {
        child->Print(out);
    }    
}

void SequenceNode::Accept(NodeVisitor &visitor) {
    visitor.Visit(this);
}

bool SequenceNode::GetMemory() const {
    return memory_;
}


// SelectorNode
SelectorNode::SelectorNode(bool memory, std::initializer_list<std::shared_ptr<Node>> children)
    : CompositionalNode(children), memory_(memory) {
}

void SelectorNode::Print(std::ostream &out) const {
    out << "Sel[id=" << GetId() << "; memory=" << GetMemory() << "; children=";
    for (auto child : GetChildren()) {
        out << child->GetId() << ",";
    }
    out << "]\n";
    for (auto child : GetChildren()) {
        child->Print(out);
    }
}

void SelectorNode::Accept(NodeVisitor &visitor) {
    visitor.Visit(this);
}

bool SelectorNode::GetMemory() const {
    return memory_;
}


// ParallelNode
ParallelNode::ParallelNode(int threshold, std::initializer_list<std::shared_ptr<Node>> children)
    : CompositionalNode(children), threshold_(threshold) {
}

void ParallelNode::Print(std::ostream &out) const {
    out << "Par[id=" << GetId() << "; threshold=" << GetThreshold() << "; children=";
    for (auto child : GetChildren()) {
        out << child->GetId() << ",";
    }
    out << "]\n";
    for (auto child : GetChildren()) {
        child->Print(out);
    }
}

void ParallelNode::Accept(NodeVisitor &visitor) {
    visitor.Visit(this);
}

int ParallelNode::GetThreshold() const {
    return threshold_;
}


// LeafNode
LeafNode::LeafNode(std::shared_ptr<Cfa> cfa)
    : Node(), cfa_(cfa) {
}

std::shared_ptr<Cfa> LeafNode::GetCfa() {
    return cfa_;
}

const std::shared_ptr<Cfa> LeafNode::GetCfa() const {
    return cfa_;
}


// ActionNode
ActionNode::ActionNode(std::shared_ptr<Cfa> cfa)
    : LeafNode(cfa) {
}

void ActionNode::Print(std::ostream &out) const {
    out << "Act[id=" << GetId() << "]\n";
    out << "CFA:\n";
    GetCfa()->Print(out);
}

void ActionNode::Accept(NodeVisitor &visitor) {
    visitor.Visit(this);
}


// ConditionNode
ConditionNode::ConditionNode(std::shared_ptr<Cfa> cfa)
    : LeafNode(cfa) {
}

void ConditionNode::Print(std::ostream &out) const {
    out << "Con[id=" << GetId() << "]\n";
    out << "CFA:\n";
    GetCfa()->Print(out);
}

void ConditionNode::Accept(NodeVisitor &visitor) {
    visitor.Visit(this);
}

} // namespace arcade::ir