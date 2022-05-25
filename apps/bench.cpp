#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

#include <glog/logging.h>

#include  "examples/example01.h"


#include "linear_encoding.h"
#include "analysis/linear/encoding.h"


int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1;

    std::vector<std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>>> examples;
    examples.push_back(arcade::example::example00());
    examples.push_back(arcade::example::example01());
    examples.push_back(arcade::example::example02());
    examples.push_back(arcade::example::example03());
    examples.push_back(arcade::example::example04());
    examples.push_back(arcade::example::example05());
    examples.push_back(arcade::example::example06());
    examples.push_back(arcade::example::example07());
    examples.push_back(arcade::example::example08());
    examples.push_back(arcade::example::example09());
    examples.push_back(arcade::example::example10());
    examples.push_back(arcade::example::example11());
    examples.push_back(arcade::example::example12());
    examples.push_back(arcade::example::example13());
    examples.push_back(arcade::example::example14());
    examples.push_back(arcade::example::example15());
    examples.push_back(arcade::example::example16());
    examples.push_back(arcade::example::example17());
    examples.push_back(arcade::example::example18());
    examples.push_back(arcade::example::example19());
    examples.push_back(arcade::example::example20());
    examples.push_back(arcade::example::example21());
    examples.push_back(arcade::example::example22());
    examples.push_back(arcade::example::example23());
    examples.push_back(arcade::example::example24());
    examples.push_back(arcade::example::example25());
    examples.push_back(arcade::example::example26());
    examples.push_back(arcade::example::example27());
    examples.push_back(arcade::example::example28());
    examples.push_back(arcade::example::example29());
    examples.push_back(arcade::example::example30());
    examples.push_back(arcade::example::example31());
    examples.push_back(arcade::example::example32());
    examples.push_back(arcade::example::example33());
    examples.push_back(arcade::example::example34());
    examples.push_back(arcade::example::example35());
    examples.push_back(arcade::example::example36());
    examples.push_back(arcade::example::example37());
    examples.push_back(arcade::example::example38());
    examples.push_back(arcade::example::example39());
    examples.push_back(arcade::example::example40());
    examples.push_back(arcade::example::example41());
    examples.push_back(arcade::example::example42());


    if (argc >= 2) {
        auto number = std::stoi(argv[1]);
        auto [root, var_manager] = examples.at(number);
        auto encoding = arcade::analysis::LinearEncoding(root, var_manager);
        auto solver = encoding.Solver();
        auto result = solver.check();
        LOG(INFO) << result;
    }
}