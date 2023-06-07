#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "Error/error_reporter.hpp"
#include "Error/interpreter_error_reporter.hpp"
#include "Error/lexer_error_reporter.hpp"
#include "Error/parser_error_reporter.hpp"
#include "Visitor/interpreter.hpp"
#include "common.hpp"
#include "Lexer/lexer.hpp"
#include "Parser/parser.hpp"
#include "Visitor/ast_printer.hpp"

int run(const std::string source) {

  auto lexer_error_reporter = std::make_shared<Lexer_error_reporter>();
  Lexer lexer {source, lexer_error_reporter};
  auto tokens = lexer.get_tokens();
  if (lexer_error_reporter->had_error()) return 65;

  auto parser_error_reporter = std::make_shared<Parser_error_reporter>();
  Parser parser {tokens, parser_error_reporter};
  auto statements = parser.parse();
  if (parser_error_reporter->had_error()) return 65;

  static Interpreter interpreter {};
  auto interpreter_error_reporter =
      std::make_shared<Interpreter_error_reporter>();
  interpreter.set_error_reporter(interpreter_error_reporter);
  interpreter.interprete(statements);
  if (interpreter_error_reporter->had_error()) return 70;

  return 0;
}

void run_prompt() {
  for (;;) {
    std::string line;
    std::cout << "> ";
    std::getline(std::cin, line);
    if (!std::cin) break;
    run(line);
  }
  std::cout << "Bye!" << common::newl;
}

void run_file(const char* filename) {
  std::ifstream in_file {filename, std::ios_base::in};
  if (!in_file) {
    std::cerr << "Failed to read file " <<
        filename << common::newl;
      std::exit(74);
  }
  std::string file_content {
      std::istreambuf_iterator<char> {in_file},
      std::istreambuf_iterator<char> {}
  };
  int status = run(file_content);
  if (status != 0) std::exit(status);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    run_prompt();
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    // TODO: Script arguments
    run_file(argv[1]);
  }
  return 0;
}
