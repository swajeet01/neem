/*
    Neem Program Language
    Copyright (C) 2023  Swajeet Swarnkar

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * */

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>

#include "Error/error_reporter.hpp"
#include "Error/interpreter_error_reporter.hpp"
#include "Error/lexer_error_reporter.hpp"
#include "Error/parser_error_reporter.hpp"
#include "Visitor/interpreter.hpp"
#include "Visitor/resolver.hpp"
#include "common.hpp"
#include "Lexer/lexer.hpp"
#include "Parser/parser.hpp"
#include "Ast/stmt.hpp"
#include "Token/token.hpp"

int run(const std::string& source, Interpreter& interpreter) {

  Lexer_error_reporter lexer_error_reporter {};
  Lexer lexer {source, lexer_error_reporter};
  std::vector<Token> tokens = lexer.get_tokens();
  if (lexer_error_reporter.had_error()) return common::EX_DATAERR;

  Parser_error_reporter parser_error_reporter {};
  Parser parser {tokens, parser_error_reporter};
  std::vector<std::shared_ptr<Stmt>> statements = parser.parse();
  if (parser_error_reporter.had_error()) return common::EX_DATAERR;

  Resolver resolver {interpreter};
  resolver.resolve(statements);
  if (interpreter.get_error_reporter().had_error()) return common::EX_SOFTWARE;

  interpreter.interprete(statements);
  if (interpreter.get_error_reporter().had_error()) return common::EX_SOFTWARE;

  return 0;
}

void run_prompt() {
  std::cout << common::notice << common::newl;
  Interpreter_error_reporter error_reporter {};
  Interpreter interpreter {error_reporter};
  for (;;) {
    std::string line;
    std::cout << ">> ";
    std::getline(std::cin, line);
    if (!std::cin) break;
    run(line, interpreter);
  }
  std::cout << "Bye!" << common::newl;
}

int run_file(const char* filename) {
  std::ifstream in_file {filename, std::ios_base::in};
  if (!in_file) {
    std::cerr << "Failed to read " <<
        filename << common::newl;
    return common::EX_IOERR;
  }
  std::string file_content {
      std::istreambuf_iterator<char> {in_file},
      std::istreambuf_iterator<char> {}
  };
  Interpreter_error_reporter error_reporter {};
  Interpreter interpreter {error_reporter};
  return run(file_content, interpreter);
}


int main(int argc, char* argv[]) {
  int status = 0;
  if (argc == 1) {
    run_prompt();
  } else if (argc == 2) {
    status = run_file(argv[1]);
  } else {
    // TODO: Script arguments
    status = run_file(argv[1]);
  }
  return status;
}
