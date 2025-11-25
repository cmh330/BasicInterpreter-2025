#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default;

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;
};

// TODO: Other statement types derived from Statement, e.g., GOTOStatement,


// LetStatement, etc.
class LetStatement : public Statement {
public:
  LetStatement(std::string source, std::string var, Expression* expr);
  ~LetStatement() override;
  void execute(VarState& state, Program& program) const override;

private:
  std::string var_;
  Expression* expr_;
};


// PrintStatement
class PrintStatement : public Statement {
public:
  PrintStatement(std::string source, Expression* expr);
  ~PrintStatement() override;
  void execute(VarState& state, Program& program) const override;

private:
  std::string var_;
  Expression* expr_;
};


// RemStatement
class RemStatement : public Statement {
public:
  RemStatement(std::string source);
  ~RemStatement() override = default;
  void execute(VarState& state, Program& program) const override;
};


// EndStatement
class EndStatement : public Statement {
public:
  EndStatement(std::string source);
  ~EndStatement() override = default;
  void execute(VarState& state, Program& program) const override;
};


// InputStatement
class InputStatement : public Statement {
public:
  InputStatement(std::string source, std::string var);
  ~InputStatement() override = default;
  void execute(VarState& state, Program& program) const override;

private:
  std::string var_;
}