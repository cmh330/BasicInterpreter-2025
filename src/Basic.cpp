#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {
      // TODO: The main function.
      TokenStream tokens = lexer.tokenize(line);
      const Token* firstToken = tokens.peek();
      // RUN
      if (firstToken && firstToken->type == TokenType::RUN) {
        program.run();
        continue;
      }
      // LIST
      if (firstToken && firstToken->type == TokenType::LIST) {
        program.list();
        continue;
      }
      // CLEAR
      if (firstToken && firstToken->type == TokenType::CLEAR) {
        program.clear();
        continue;
      }
      // QUIT
      if (firstToken && firstToken->type == TokenType::QUIT) {
        return 0;
      }
      // HELP
      if (firstToken && firstToken->type == TokenType::HELP) {
        continue;
      }
      ParsedLine parsed = parser.parseLine(tokens, line);
      // 检查是否有行号
      if (parsed.getLine().has_value()) {
        // 有行号
        int line = parsed.getLine().value();
        Statement* stmt = parsed.fetchStatement();
        if (stmt == nullptr) {
          // 只有一个行号
          program.removeStmt(line);
        } else {
          // 把这一行添加进去
          try {
            program.addStmt(line, stmt);
          } catch (...) {
            delete stmt;
            throw;
          }
        }
      } else {
        // 没有行号
        Statement* stmt = parsed.fetchStatement();
        if (stmt != nullptr) {
          try {
            program.execute(stmt);
            delete stmt;
          } catch (...) {
            delete stmt;
            throw;
          }
        }
      }
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}