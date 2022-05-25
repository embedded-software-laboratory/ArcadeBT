#ifndef IR_CFA
#define IR_CFA

#include <memory>
#include <optional>
#include <vector>

#include "statement.h"

namespace arcade::ir {

class Location;

class Transition {
public:
    Transition(std::shared_ptr<Statement> statement, std::weak_ptr<Location> to_location);

    void SetToLocation(std::weak_ptr<Location> to_location);
    std::weak_ptr<Location> ToLocation();

    const std::shared_ptr<Statement> GetStatement() const;
private:
    std::shared_ptr<Statement> statement_;
    std::weak_ptr<Location> to_location_;
};

class Location {
public:
    Location(unsigned id);

    std::shared_ptr<Transition> AddTransition(std::shared_ptr<Statement> statement, std::weak_ptr<Location> to);
    std::vector<std::shared_ptr<Transition>> GetTransitions();

    unsigned GetId() const;
private:
    unsigned id_;
    std::vector<std::shared_ptr<Transition>> transitions_; // outgoing transitions
};

// TODO class nedded?
class BranchInformation {
public:
private:
    BranchType branch_type_; // TODO needed (?) or two vectors in cfa
    std::shared_ptr<Location> branch_location_;
    std::shared_ptr<Transition> primary_transition_;
    std::shared_ptr<Transition> secondary_transition_;
};

class Cfa {
public:
    std::shared_ptr<Location> AddLocation();
    bool RemoveLocation(std::shared_ptr<Location>);

    std::shared_ptr<Location> GetInitialLocation();
    void SetInitialLocation(std::shared_ptr<Location> location);

    std::optional<std::shared_ptr<Location>> GetSuccessLocation();
    void SetSuccessLocation(std::shared_ptr<Location> location);
    std::optional<std::shared_ptr<Location>> GetRunningLocation();
    void SetRunningLocation(std::shared_ptr<Location> location);
    std::optional<std::shared_ptr<Location>> GetFailureLocation();
    void SetFailureLocation(std::shared_ptr<Location> location);

    std::vector<std::shared_ptr<Location>> GetLocations();
    const std::vector<std::shared_ptr<Location>> GetLocations() const;

    void Print(std::ostream &out) const;
private:
    std::vector<std::shared_ptr<Location>> locations_;
    std::shared_ptr<Location> initial_location_;
    std::optional<std::shared_ptr<Location>> success_location_; // TODO remove optional?
    std::optional<std::shared_ptr<Location>> running_location_;
    std::optional<std::shared_ptr<Location>> failure_location_;

    unsigned next_id_ = 0;
};

class CfaBuilder;

class CfaBuilderHandle {
public:
    CfaBuilderHandle(CfaBuilder *builder, std::shared_ptr<Location> current_location, std::shared_ptr<Location> merge_location = nullptr);
    void AddAssignment(BooleanExpressionHandle variable, BooleanExpressionHandle expression);
    void AddAssignment(ArithmeticExpressionHandle variable, ArithmeticExpressionHandle expression);
    void AddAssume(BooleanExpressionHandle condition);
    void AddAssert(BooleanExpressionHandle condition);
    void AddReturn(const ReturnValue &return_value);
    std::pair<std::shared_ptr<CfaBuilderHandle>, std::shared_ptr<CfaBuilderHandle>> AddIf(BooleanExpressionHandle condition);
    std::shared_ptr<CfaBuilderHandle> AddWhile(BooleanExpressionHandle condition);
    
    friend CfaBuilder;
private:
    CfaBuilder *builder_;
    std::shared_ptr<Location> current_;
    std::shared_ptr<Location> merge_with_;
    
    void Merge();
};

class CfaBuilder {
public:
    CfaBuilder();
    std::shared_ptr<CfaBuilderHandle> AddInitialLocation();

    std::shared_ptr<Cfa> GetCfa(bool finalize = true);

    friend CfaBuilderHandle;
private:
    std::shared_ptr<Cfa> cfa_;
    std::vector<std::shared_ptr<CfaBuilderHandle>> handles_;

    void Register(std::shared_ptr<CfaBuilderHandle> handle);
    void Deregister(std::shared_ptr<CfaBuilderHandle> handle);
};

} // namespace arcade::ir

#endif // IR_CFA