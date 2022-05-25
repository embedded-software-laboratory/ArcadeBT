#include "cfa.h"

#include <algorithm>
#include <exception>
#include <sstream>

namespace arcade::ir {

// Transition
Transition::Transition(std::shared_ptr<Statement> statement, std::weak_ptr<Location> to_location)
    : statement_(statement), to_location_(to_location) {
}

void Transition::SetToLocation(std::weak_ptr<Location> to_location) {
    to_location_ = to_location;
}

std::weak_ptr<Location> Transition::ToLocation() {
    return to_location_;
}

const std::shared_ptr<Statement> Transition::GetStatement() const {
    return statement_;
}


// Location
Location::Location(unsigned id)
    : id_(id) {
}

std::shared_ptr<Transition> Location::AddTransition(std::shared_ptr<Statement> statement, std::weak_ptr<Location> to) {
     auto transition = std::make_shared<Transition>(statement, to);
     transitions_.push_back(transition);
     return transition;
}

std::vector<std::shared_ptr<Transition>> Location::GetTransitions() {
    return transitions_;
}

unsigned Location::GetId() const {
    return id_;
}


// Cfa
std::shared_ptr<Location> Cfa::AddLocation() {
    auto location = std::make_shared<Location>(next_id_);
    next_id_++;
    locations_.push_back(location);
    return location;
}

bool Cfa::RemoveLocation(std::shared_ptr<Location> location) {
    auto it = std::find(locations_.cbegin(), locations_.cend(), location);
    if (it != locations_.cend()) {
        locations_.erase(it);
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<Location> Cfa::GetInitialLocation() {
    return initial_location_;
}

void Cfa::SetInitialLocation(std::shared_ptr<Location> location) {
    initial_location_ = location;
}

std::optional<std::shared_ptr<Location>> Cfa::GetSuccessLocation() {
    return success_location_;
}

void Cfa::SetSuccessLocation(std::shared_ptr<Location> location) {
    success_location_ = location;
}

std::optional<std::shared_ptr<Location>> Cfa::GetRunningLocation() {
    return running_location_;
}

void Cfa::SetRunningLocation(std::shared_ptr<Location> location) {
    running_location_ = location;
}

std::optional<std::shared_ptr<Location>> Cfa::GetFailureLocation() {
    return failure_location_;
}

void Cfa::SetFailureLocation(std::shared_ptr<Location> location) {
    failure_location_ = location;
}

std::vector<std::shared_ptr<Location>> Cfa::GetLocations() {
    return locations_;
}

const std::vector<std::shared_ptr<Location>> Cfa::GetLocations() const {
    return locations_;
}

void Cfa::Print(std::ostream &out) const {
    out << "  initial: " << ((initial_location_) ? std::to_string(initial_location_->GetId()) : "no initial location") << "\n";
    out << "  success: " << ((success_location_) ? std::to_string((*success_location_)->GetId()) : "no success location") << "\n";
    out << "  running: " << ((running_location_) ? std::to_string((*running_location_)->GetId()) : "no running location") << "\n";
    out << "  failure: " << ((failure_location_) ? std::to_string((*failure_location_)->GetId()) : "no failure location") << "\n";

    out << "Transitions:\n";
    for (auto location : GetLocations()) {
        for (auto transition : location->GetTransitions()) {
            out << "  " << location->GetId() << " -> ";
            transition->GetStatement()->Print(out);
            out << " -> " << transition->ToLocation().lock()->GetId() << "\n";
        }
    }
    out << "\n";
}


// CfaBuilderHandle
// TODO add nullptr check
CfaBuilderHandle::CfaBuilderHandle(CfaBuilder *builder, std::shared_ptr<Location> current_location, std::shared_ptr<Location> merge_location)
    : builder_(builder), current_(current_location), merge_with_(merge_location) {
}

void CfaBuilderHandle::AddAssignment(BooleanExpressionHandle variable, BooleanExpressionHandle expression) {
    auto var = std::dynamic_pointer_cast<BooleanVariable>(variable.Expression());
    if (var == nullptr) {
        std::stringstream ss;
        variable.Expression()->Print(ss);
        throw std::logic_error("expression \"" + ss.str() + "\" is not a boolean variable");
    }
    auto new_location = builder_->GetCfa(false)->AddLocation();
    current_->AddTransition(std::make_shared<BooleanAssignment>(var, expression.Expression()), new_location);
    current_ = new_location;
}

void CfaBuilderHandle::AddAssignment(ArithmeticExpressionHandle variable, ArithmeticExpressionHandle expression) {
    auto var = std::dynamic_pointer_cast<IntegerVariable>(variable.Expression());
    if (var == nullptr) {
        std::stringstream ss;
        variable.Expression()->Print(ss);
        throw std::logic_error("expression \"" + ss.str() + "\" is not a integer variable");
    }
    auto new_location = builder_->GetCfa(false)->AddLocation();
    current_->AddTransition(std::make_shared<IntegerAssignment>(var, expression.Expression()), new_location);
    current_ = new_location;
}

void CfaBuilderHandle::AddAssume(BooleanExpressionHandle condition) {
    auto new_location = builder_->GetCfa(false)->AddLocation();
    current_->AddTransition(std::make_shared<AssumeStatement>(condition.Expression()), new_location);
    current_ = new_location;
}

void CfaBuilderHandle::AddAssert(BooleanExpressionHandle condition) {
    auto new_location = builder_->GetCfa(false)->AddLocation();
    current_->AddTransition(std::make_shared<AssertStatement>(condition.Expression()), new_location);
    current_ = new_location;
}

void CfaBuilderHandle::AddReturn(const ReturnValue &return_value) {
    std::shared_ptr<Location> target = nullptr;
    switch (return_value)
    {
    case ReturnValue::kSuccess:
        if (builder_->GetCfa(false)->GetSuccessLocation()) {
            target = *builder_->GetCfa(false)->GetSuccessLocation();
        } else {
            target = builder_->GetCfa(false)->AddLocation();
            builder_->GetCfa(false)->SetSuccessLocation(target);
        }
        break;
    case ReturnValue::kRunning:
        if (builder_->GetCfa(false)->GetRunningLocation()) {
            target = *builder_->GetCfa(false)->GetRunningLocation();
        } else {
            target = builder_->GetCfa(false)->AddLocation();
            builder_->GetCfa(false)->SetRunningLocation(target);
        }
        break;
    case ReturnValue::kFailure:
        if (builder_->GetCfa(false)->GetFailureLocation()) {
            target = *builder_->GetCfa(false)->GetFailureLocation();
        } else {
            target = builder_->GetCfa(false)->AddLocation();
            builder_->GetCfa(false)->SetFailureLocation(target);
        }
        break;
    default:
        throw std::logic_error("unknown return type");
        break;
    }
    current_->AddTransition(std::make_shared<ReturnStatement>(return_value), target);
    current_ = nullptr;
    merge_with_ = nullptr;
}

std::pair<std::shared_ptr<CfaBuilderHandle>, std::shared_ptr<CfaBuilderHandle>> CfaBuilderHandle::AddIf(BooleanExpressionHandle condition) {
    auto then_branch_location = builder_->GetCfa(false)->AddLocation();
    auto else_branch_location = builder_->GetCfa(false)->AddLocation();

    auto then_transition = current_->AddTransition(std::make_shared<BranchStatement>(condition.Expression(), true, BranchType::kIf, std::weak_ptr<Transition>()), then_branch_location);
    auto else_transition = current_->AddTransition(std::make_shared<BranchStatement>((!condition).Expression(), false, BranchType::kIf, std::weak_ptr<Transition>()), else_branch_location);
    std::dynamic_pointer_cast<BranchStatement>(then_transition->GetStatement())->SetOtherBranch(else_transition);
    std::dynamic_pointer_cast<BranchStatement>(else_transition->GetStatement())->SetOtherBranch(then_transition);

    auto merge_location = builder_->GetCfa(false)->AddLocation();
    current_ = merge_location;

    auto then_handle = std::make_shared<CfaBuilderHandle>(builder_, then_branch_location, merge_location);
    auto else_handle = std::make_shared<CfaBuilderHandle>(builder_, else_branch_location, merge_location);
    builder_->Register(then_handle);
    builder_->Register(else_handle);
    return {then_handle, else_handle};
}

std::shared_ptr<CfaBuilderHandle> CfaBuilderHandle::AddWhile(BooleanExpressionHandle condition) {
    auto entry_location = builder_->GetCfa(false)->AddLocation();
    auto exit_location = builder_->GetCfa(false)->AddLocation();

    auto entry_transition = current_->AddTransition(std::make_shared<BranchStatement>(condition.Expression(), true, BranchType::kWhile, std::weak_ptr<Transition>()), entry_location);
    auto exit_transition = current_->AddTransition(std::make_shared<BranchStatement>((!condition).Expression(), false, BranchType::kWhile, std::weak_ptr<Transition>()), exit_location);
    std::dynamic_pointer_cast<BranchStatement>(entry_transition->GetStatement())->SetOtherBranch(exit_transition);
    std::dynamic_pointer_cast<BranchStatement>(exit_transition->GetStatement())->SetOtherBranch(entry_transition);

    auto entry_handle = std::make_shared<CfaBuilderHandle>(builder_, entry_location, current_);
    builder_->Register(entry_handle);
    current_ = exit_location;

    return entry_handle;
}

void CfaBuilderHandle::Merge() {
    if (merge_with_ == nullptr) {
        return;
    }

    for (auto location : builder_->GetCfa(false)->GetLocations()) {
        for (auto transition : location->GetTransitions()) {
            if (transition->ToLocation().lock() == current_) {
                transition->SetToLocation(merge_with_);
            }
        }
    }
    builder_->GetCfa(false)->RemoveLocation(current_);

    current_ = nullptr;
    merge_with_ = nullptr;
}


// CfaBuilder
CfaBuilder::CfaBuilder()
    : cfa_(std::make_shared<Cfa>()) {
}

std::shared_ptr<CfaBuilderHandle> CfaBuilder::AddInitialLocation() {
    auto location = cfa_->AddLocation();
    cfa_->SetInitialLocation(location);
    
    auto handle = std::make_shared<CfaBuilderHandle>(this, location);
    Register(handle);
    return handle;
}

std::shared_ptr<Cfa> CfaBuilder::GetCfa(bool finalize) {
    if (finalize) {
        std::for_each(handles_.rbegin(), handles_.rend(),
            [](auto &handle){
                handle->Merge();
        });
    }
    return cfa_;
}

void CfaBuilder::Register(std::shared_ptr<CfaBuilderHandle> handle) {
    handles_.push_back(handle);
}

// TODO needed?
void CfaBuilder::Deregister(std::shared_ptr<CfaBuilderHandle> handle) {
    auto it = std::find(handles_.cbegin(), handles_.cend(), handle);
    if (it != handles_.cend()) {
        handles_.erase(it);
    }
}


} // namespace arcade::ir