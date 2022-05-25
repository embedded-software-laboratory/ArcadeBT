#include "variable.h"

namespace arcade::analysis
{

// static
std::string Variable::kGlobalPrefix = "g_";
std::string Variable::kLocalPrefix = "l_";
std::string Variable::kPrimeSuffix = "_p";

Variable Variable::CreateGlobalIntegerVariable(z3::context &context, const std::string &name) {
    auto var = context.int_const((Variable::kGlobalPrefix + name).c_str());
    auto var_prime = context.int_const((Variable::kGlobalPrefix + name + Variable::kPrimeSuffix).c_str());
    return Variable(var, var_prime);
}

Variable Variable::CreateGlobalBooleanVariable(z3::context &context, const std::string &name) {
    auto var = context.bool_const((Variable::kGlobalPrefix + name).c_str());
    auto var_prime = context.bool_const((Variable::kGlobalPrefix + name + Variable::kPrimeSuffix).c_str());
    return Variable(var, var_prime);    
}

Variable Variable::CreateLocalIntegerVariable(z3::context &context, const std::string &name, unsigned node_id) {
    auto var = context.int_const((Variable::kLocalPrefix + std::to_string(node_id) + "_" + name).c_str());
    auto var_prime = context.int_const((Variable::kLocalPrefix + std::to_string(node_id) + name + Variable::kPrimeSuffix).c_str());
    return Variable(var, var_prime);
}

Variable Variable::CreateLocalBooleanVariable(z3::context &context, const std::string &name, unsigned node_id) {
    auto var = context.bool_const((Variable::kLocalPrefix + std::to_string(node_id) + "_" + name).c_str());
    auto var_prime = context.bool_const((Variable::kLocalPrefix + std::to_string(node_id) + name + Variable::kPrimeSuffix).c_str());
    return Variable(var, var_prime);
}

Variable Variable::CreateIntegerVariable(z3::context &context, const std::string &name) {
    auto var = context.int_const(name.c_str());
    auto var_prime = context.int_const((name + Variable::kPrimeSuffix).c_str());
    return Variable(var, var_prime);
}

Variable Variable::CreateBooleanVariable(z3::context &context, const std::string &name) {
    auto var = context.bool_const(name.c_str());
    auto var_prime = context.bool_const((name + Variable::kPrimeSuffix).c_str());
    return Variable(var, var_prime);
}


// Variable
Variable::Variable(z3::expr variable, z3::expr variable_primed)
    : variable_(variable), variable_primed_(variable_primed) {
}

z3::expr Variable::Get() {
    return variable_;
}

z3::expr Variable::Prime() {
    return variable_primed_;
}


} // namespace arcade::analysis