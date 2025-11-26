#include "Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }

// TODO: Imply interfaces declared in the Statement.hpp.
// LetStatement
LetStatement::LetStatement(std::string source, std::string var,
                            Expression* expr) : Statement(std::move(source)),
                            var_(std::move(var)), expr_(expr) {}
LetStatement::~LetStatement() {
  delete expr_;
}
void LetStatement::execute(VarState& state, Program& program) const{
  int value = expr_->evaluate(state);
  state.setValue(var_, value);
}


// PrintStatement
PrintStatement::PrintStatement(std::string source, Expression* expr) : Statement(std::move(source)), expr_(expr){}
PrintStatement::~PrintStatement() {delete expr_;}
void PrintStatement::execute(VarState& state, Program& program) const {
  int value = expr_->evaluate(state);
  std::cout << value << '\n';
}


// RemStatement
RemStatement::RemStatement(std::string source) : Statement(std::move(source)) {}
void RemStatement::execute(VarState& state, Program& program) const {}


// EndStatement
EndStatement::EndStatement(std::string source) : Statement(std::move(source)) {}
void EndStatement::execute(VarState& state, Program& program) const {
  program.programEnd();
}


// InputStatement
InputStatement::InputStatement(std::string source, std::string var) : Statement(std::move(source)), var_(std::move(var)) {}
void InputStatement::execute(VarState& state, Program& program) const {
  std::cout << "?";
  std::string input;
  std::getline(std::cin, input);

  if (input.empty()) {
    throw BasicError("INVALID NUMBER");
  }

  size_t start = 0;
  bool negative = false;
  if (input[0] == '-') {
    if (input.length() == 1) {  // only a '-'
      throw BasicError("INVALID NUMBER");
    }
    start = 1;
    negative = true;
  }

  long int value = 0;
  for (size_t i = start; i < input.length(); i++) {
    if (input[i] < '0' || input[i] > '9') {
      throw BasicError("INVALID NUMBER");
    }
    int digit = input[i] - '0';
    if (value > 214748364) {
      // 溢出了
      throw BasicError("INVALID NUMBER");
    }
    value = value * 10 + digit;
  }
  if (negative) {
    value = -value;
  }
  state.setValue(var_, value);
}