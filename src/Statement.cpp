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

  size_t pos;
  int value = std::stoi(input, &pos);
  if (pos != input.size()) {
    std::cout << "INVALID NUMBER\n";
  } else state.setValue(var_, value);

}