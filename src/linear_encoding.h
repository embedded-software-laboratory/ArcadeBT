#ifndef LINEAR_ENCODING
#define LINEAR_ENCODING

#include <map>
#include <memory>

#include <z3++.h>

#include "ir/bt.h"

namespace arcade::analysis {

class LinearEncoding {
public:
    LinearEncoding(std::shared_ptr<arcade::ir::Node> behavior_tree, std::shared_ptr<arcade::ir::VariableManager> variable_manager);

    z3::solver Solver();
private:
    std::shared_ptr<arcade::ir::Node> behavior_tree_;
    std::shared_ptr<arcade::ir::VariableManager> variable_manager_;

    z3::context context_;
    z3::solver solver_;



    // variables
    std::vector<std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>>> variables_; // pairs of z3 variables primed and unprimed
    z3::expr_vector initialization_;
    std::map<std::shared_ptr<z3::expr>, bool> nondeterministic_; // variables
    // sequence & selector
    std::map<std::shared_ptr<arcade::ir::Node>, std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>>> memory_variable_map_;
    // parallel
    std::map<std::shared_ptr<arcade::ir::Node>, std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>>> success_count_variable_map_;
    std::map<std::shared_ptr<arcade::ir::Node>, std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>>> running_count_variable_map_;
    std::map<std::shared_ptr<arcade::ir::Node>, std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>>> failure_count_variable_map_;
    std::map<std::shared_ptr<arcade::ir::Node>, std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>>> completed_variable_map_;
    // program (global and local cfa)
    std::map<std::shared_ptr<arcade::ir::IntegerVariable>, std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>>> integer_variable_map_;
    std::map<std::shared_ptr<arcade::ir::BooleanVariable>, std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>>> boolean_variable_map_;

    void CreateVariables();
    std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>> CreateIntegerVariablePair(const std::string &name);
    std::pair<std::shared_ptr<z3::expr>, std::shared_ptr<z3::expr>> CreateBooleanVariablePair(const std::string &name);
    void CreateVariables(std::shared_ptr<arcade::ir::Node> node);
    void CreateVariables(std::shared_ptr<arcade::ir::SequenceNode> node);
    void CreateVariables(std::shared_ptr<arcade::ir::SelectorNode> node);
    void CreateVariables(std::shared_ptr<arcade::ir::ParallelNode> node);
    void CreateVariables(std::shared_ptr<arcade::ir::ActionNode> node);
    void CreateVariables(std::shared_ptr<arcade::ir::ConditionNode> node);
    void CreateVariables(int node_id, std::shared_ptr<arcade::ir::Cfa> cfa);

    // predicates
    std::map<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<z3::func_decl>> tick_predicate_map_;
    std::map<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<z3::func_decl>> success_predicate_map_;
    std::map<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<z3::func_decl>> running_predicate_map_;
    std::map<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<z3::func_decl>> failure_predicate_map_;
    std::map<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<z3::func_decl>> intermediate_predicate_map_;
    std::map<std::shared_ptr<arcade::ir::Location>, std::shared_ptr<z3::func_decl>> location_predicate_map_;

    void CreatePredicates();
    void CreatePredicates(std::shared_ptr<arcade::ir::Node> node);
    void CreatePredicates(std::shared_ptr<arcade::ir::SequenceNode> node);
    void CreatePredicates(std::shared_ptr<arcade::ir::SelectorNode> node);
    void CreatePredicates(std::shared_ptr<arcade::ir::ParallelNode> node);
    void CreatePredicates(std::shared_ptr<arcade::ir::ActionNode> node);
    void CreatePredicates(std::shared_ptr<arcade::ir::ConditionNode> node);
    void CreatePredicates(int node_id, std::shared_ptr<arcade::ir::Cfa> cfa);
    z3::sort_vector Domain();

    // rules
    void CreateRules();
    void CreateRules(std::shared_ptr<arcade::ir::Node> node);
    void CreateRules(std::shared_ptr<arcade::ir::SequenceNode> node);
    void CreateRules(std::shared_ptr<arcade::ir::SelectorNode> node);
    void CreateRules(std::shared_ptr<arcade::ir::ParallelNode> node);
    void CreateRules(std::shared_ptr<arcade::ir::ActionNode> node);
    void CreateRules(std::shared_ptr<arcade::ir::ConditionNode> node);
    void CreateRules(std::shared_ptr<arcade::ir::Cfa> cfa);

    z3::expr_vector Variables();
    z3::expr_vector VariablesPrimed();
    z3::expr_vector VariablesAndPrimed();

    z3::expr Tick(std::shared_ptr<arcade::ir::Node> node);
    z3::expr TickPrime(std::shared_ptr<arcade::ir::Node> node);
    z3::expr Success(std::shared_ptr<arcade::ir::Node> node);
    z3::expr SuccessPrime(std::shared_ptr<arcade::ir::Node> node);
    z3::expr Running(std::shared_ptr<arcade::ir::Node> node);
    z3::expr RunningPrime(std::shared_ptr<arcade::ir::Node> node);
    z3::expr Failure(std::shared_ptr<arcade::ir::Node> node);
    z3::expr FailurePrime(std::shared_ptr<arcade::ir::Node> node);
    z3::expr Location(std::shared_ptr<arcade::ir::Location> location);
    z3::expr LocationPrime(std::shared_ptr<arcade::ir::Location> location);
    z3::expr Intermediate(std::shared_ptr<arcade::ir::Node> node);
    z3::expr IntermediatePrime(std::shared_ptr<arcade::ir::Node> node);

    // encoding statements
    z3::expr Encode(std::shared_ptr<arcade::ir::Statement> statement);
    z3::expr Encode(std::shared_ptr<arcade::ir::IntegerAssignment> statement);
    z3::expr Encode(std::shared_ptr<arcade::ir::BooleanAssignment> statement);
    z3::expr Encode(std::shared_ptr<arcade::ir::AssertStatement> statement);
    z3::expr Encode(std::shared_ptr<arcade::ir::AssumeStatement> statement);
    z3::expr Encode(std::shared_ptr<arcade::ir::ReturnStatement> statement);
    // encoding expressions
    z3::expr Encode(std::shared_ptr<arcade::ir::Expression> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::UnaryArithmeticOperation> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::BinaryArithmeticOperation> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::UnaryBooleanOperation> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::BinaryBooleanOperation> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::BinaryArithmeticComparisionOperation> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::BooleanLiteral> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::ArithmeticLiteral> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::IntegerVariable> expression);
    z3::expr Encode(std::shared_ptr<arcade::ir::BooleanVariable> expression);

    void CreateLoop();
    void CreateInitialization();

    z3::expr Id(std::vector<std::shared_ptr<z3::expr>> except);
};

}


#endif // LINEAR_ENCODING