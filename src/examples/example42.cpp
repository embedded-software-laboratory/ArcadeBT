#include "example01.h"

namespace arcade::example {

// parallel
// example

// sat
std::pair<std::shared_ptr<arcade::ir::Node>, std::shared_ptr<arcade::ir::VariableManager>> example42() {
    using namespace arcade::ir;
    auto variable_manager = std::make_shared<VariableManager>();
    // global variables
    auto robot_on = variable_manager->AddGlobalBooleanVariable("robot_on", false, AccessType::kWrite);
    auto collision_detected = variable_manager->AddGlobalBooleanVariable("collision_detected", false, AccessType::kWrite);
    auto obstacle_detected = variable_manager->AddGlobalBooleanVariable("obstacle_detected", false, AccessType::kWrite);
    auto target = variable_manager->AddGlobalIntegerVariable("target", 0, AccessType::kWrite);

    auto nd = variable_manager->AddGlobalIntegerVariable("nd", false, AccessType::kRead);
    auto n = variable_manager->AddGlobalIntegerVariable("n", false, AccessType::kWrite);

    auto fd = variable_manager->AddGlobalBooleanVariable("fd", false, AccessType::kRead);
    auto f = variable_manager->AddGlobalBooleanVariable("f", false, AccessType::kWrite);


    // node A
    auto builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(robot_on);
        {
            then_handle->AddReturn(ReturnValue::kFailure);
        }   
        {
            else_handle->AddReturn(ReturnValue::kSuccess);
        }
        
        
    }
    auto node_A = std::make_shared<ConditionNode>(builder.GetCfa());

    // node BA
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(collision_detected);
        {
            then_handle->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle->AddReturn(ReturnValue::kFailure);
        }
    }
    auto node_BA = std::make_shared<ConditionNode>(builder.GetCfa());

    // node BBa
    builder = CfaBuilder();
    { 
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(obstacle_detected);
        {
            then_handle->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle->AddReturn(ReturnValue::kFailure);
        }
    }
    auto node_BBa = std::make_shared<ConditionNode>(builder.GetCfa());

    // node BCAa
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(target == 0);
        {
            then_handle->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle->AddReturn(ReturnValue::kFailure);
        }
    }
    auto node_BCAa = std::make_shared<ConditionNode>(builder.GetCfa());

    // node BackToBase
    builder = CfaBuilder();
    {
        auto cfa = builder.GetCfa(false);
        auto timer = variable_manager->AddLocalIntegerVariable("timer", 0, AccessType::kWrite, cfa);

        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(timer == 20);
        {
            then_handle->AddAssignment(timer, 0);
        }
        handle->AddAssignment(timer, timer + 1);
        auto [then_handle2, else_handle2] = handle->AddIf(timer == 20);
        {
            then_handle2->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle2->AddReturn(ReturnValue::kRunning);
        }  
    }
    auto node_BackToBase = std::make_shared<ActionNode>(builder.GetCfa());

    // node PowerOff
    builder = CfaBuilder();
    {
        auto cfa = builder.GetCfa(false);
        auto timer = variable_manager->AddLocalIntegerVariable("timer", 0, AccessType::kWrite, cfa);

        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(timer == 1);
        {
            then_handle->AddAssignment(timer, 0);
        }
        handle->AddAssignment(timer, timer + 1);
        auto [then_handle2, else_handle2] = handle->AddIf(timer == 1);
        {
            then_handle2->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle2->AddReturn(ReturnValue::kRunning);
        }
    }
    auto node_PowerOff = std::make_shared<ActionNode>(builder.GetCfa());

    // node MoveToTargetFast
    builder = CfaBuilder();
    {
        auto cfa = builder.GetCfa(false);
        auto timer = variable_manager->AddLocalIntegerVariable("timer", 0, AccessType::kWrite, cfa);

        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(timer == 30);
        {
            then_handle->AddAssignment(timer, 0);
        }
        handle->AddAssignment(timer, timer + 1);
        auto [then_handle2, else_handle2] = handle->AddIf(timer == 30);
        {
            then_handle2->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle2->AddReturn(ReturnValue::kRunning);
        }
    }
    auto node_MoveToTargetFast = std::make_shared<ActionNode>(builder.GetCfa());

    // node MoveToTargetSlow
    builder = CfaBuilder();
    {
        auto cfa = builder.GetCfa(false);
        auto timer = variable_manager->AddLocalIntegerVariable("timer", 0, AccessType::kWrite, cfa);

        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(timer == 50);
        {
            then_handle->AddAssignment(timer, 0);
        }
        handle->AddAssignment(timer, timer + 1);
        auto [then_handle2, else_handle2] = handle->AddIf(timer == 50);
        {
            then_handle2->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle2->AddReturn(ReturnValue::kRunning);
        }
    }
    auto node_MoveToTargetSlow = std::make_shared<ActionNode>(builder.GetCfa());

    // node DoWork
    builder = CfaBuilder();
    {
        auto cfa = builder.GetCfa(false);
        auto timer = variable_manager->AddLocalIntegerVariable("timer", 0, AccessType::kWrite, cfa);

        auto handle = builder.AddInitialLocation();
        handle->AddAssert(robot_on & !collision_detected & !obstacle_detected);
        auto [then_handle, else_handle] = handle->AddIf(timer == 15);
        {
            then_handle->AddAssignment(timer, 0);
        }
        handle->AddAssignment(timer, timer + 1);
        auto [then_handle2, else_handle2] = handle->AddIf(timer == 15);
        {
            then_handle2->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle2->AddReturn(ReturnValue::kRunning);
        }
    }
    auto node_DoWork = std::make_shared<ActionNode>(builder.GetCfa());

    // node BackToBase2
    builder = CfaBuilder();
    {
        auto cfa = builder.GetCfa(false);
        auto timer = variable_manager->AddLocalIntegerVariable("timer", 0, AccessType::kWrite, cfa);

        auto handle = builder.AddInitialLocation();
        auto [then_handle, else_handle] = handle->AddIf(timer == 20);
        {
            then_handle->AddAssignment(timer, 0);
        }
        handle->AddAssignment(timer, timer + 1);
        auto [then_handle2, else_handle2] = handle->AddIf(timer == 20);
        {
            then_handle2->AddReturn(ReturnValue::kSuccess);
        }
        {
            else_handle2->AddReturn(ReturnValue::kRunning);
        }
    }
    auto node_BackToBase2 = std::make_shared<ActionNode>(builder.GetCfa());

    // node Environment
    builder = CfaBuilder();
    {
        auto handle = builder.AddInitialLocation();
        handle->AddAssignment(robot_on, fd);
        handle->AddAssignment(collision_detected, fd);
        handle->AddAssignment(obstacle_detected, fd);
        handle->AddAssignment(target, nd);
        handle->AddReturn(ReturnValue::kSuccess);

    }
    auto node_Environment = std::make_shared<ActionNode>(builder.GetCfa());

    // node BCA
    std::initializer_list<std::shared_ptr<Node>> children = {node_BCAa, node_BackToBase};
    auto node_BCA = std::make_shared<SequenceNode>(false, children);

    // node BCB 
    children = {node_MoveToTargetFast, node_MoveToTargetSlow, node_DoWork, node_BackToBase2};
    auto node_BCB = std::make_shared<SequenceNode>(false, children);

    // node BC
    children = {node_BCA, node_BCB};
    auto node_BC = std::make_shared<SelectorNode>(false, children);

    // node BB
    children = {node_BBa, node_PowerOff};
    auto node_BB = std::make_shared<SequenceNode>(false, children);

    // node B
    children = {node_BA, node_BB, node_BC};
    auto node_B = std::make_shared<SelectorNode>(false, children);

    // robot
    children = {node_A, node_B};
    auto node_robot = std::make_shared<SelectorNode>(false, children);

    // root
    children = {node_robot, node_Environment};
    auto node_root = std::make_shared<ParallelNode>(2, children);

    return {node_root, variable_manager};
}
    
} 