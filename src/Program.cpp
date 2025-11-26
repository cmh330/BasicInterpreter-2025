// TODO: Imply interfaces declared in the Program.hpp.
#include "Program.hpp"
#include <iostream>
#include "Statement.hpp"
#include "utils/Error.hpp"

Program::Program(): programCounter_(-1), programEnd_(false) {}

void Program::addStmt(int line, Statement* stmt) {
  recorder_.add(line, stmt);
}

void Program::removeStmt(int line) {
  recorder_.remove(line);
}

void Program::run() {
  resetAfterRun();
  programCounter_ = recorder_.nextLine(-1);
  if (programCounter_ == -1) {
    return;
  }
  while (!programEnd_ && programCounter_ != -1) {
    const Statement* stmt = recorder_.get(programCounter_);
    if (stmt == nullptr) {
      throw BasicError("LINE NUMBER ERROR");
    }
    programCounter_ = recorder_.nextLine(programCounter_);
    stmt->execute(vars_, *this);
  }
  resetAfterRun();
}

void Program::list() const {
  recorder_.printLines();
}

void Program::clear() {
  recorder_.clear();
  vars_.clear();
  programCounter_ = -1;
  programEnd_ = false;
}

void Program::execute(Statement* stmt) {
  stmt->execute(vars_, *this);
}

int Program::getPC() const noexcept {
  return programCounter_;
}

void Program::changePC(int line) {
  if (!recorder_.hasLine(line)) {
    throw BasicError("LINE NUMBER ERROR");
  }
  programCounter_ = line;
}

void Program::programEnd() {
  programEnd_ = true;
}

void Program::resetAfterRun() noexcept {
  programCounter_ = -1;
  programEnd_ = false;
  vars_.clear();
}