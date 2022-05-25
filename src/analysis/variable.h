#ifndef ANALYSIS_VARIABLE
#define ANALYSIS_VARIABLE

#include <string>

#include "z3++.h"

namespace arcade::analysis
{

/*
nameing convetions
global: g_NAME
global primed g_NAME_p
local: l_ID_NAME
local primed l_ID_NAME_p
*/
class Variable {
public:
    static std::string kGlobalPrefix;
    static std::string kLocalPrefix;
    static std::string kPrimeSuffix;

    static Variable CreateGlobalIntegerVariable(z3::context &context, const std::string &name);
    static Variable CreateGlobalBooleanVariable(z3::context &context, const std::string &name);

    static Variable CreateLocalIntegerVariable(z3::context &context, const std::string &name, unsigned node_id);
    static Variable CreateLocalBooleanVariable(z3::context &context, const std::string &name, unsigned node_id);

    // do not use prefix
    static Variable CreateIntegerVariable(z3::context &context, const std::string &name);
    static Variable CreateBooleanVariable(z3::context &context, const std::string &name);    

    z3::expr Get();
    z3::expr Prime();
private:
    Variable(z3::expr variable, z3::expr variable_primed);

    z3::expr variable_;
    z3::expr variable_primed_;
};

} // namespace arcade::analysis


#endif // ANALYSIS_VARIABLE