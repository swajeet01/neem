#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "Error/error_reporter.h"
#include "Error/lexer_error_reporter.h"
#include "Error/parser_error_reporter.h"
#include "common.h"
#include "Lexer/lexer.h"
#include "Parser/parser.h"
#include "Visitor/ast_printer.h"

void run(const std::string source) {
  auto lexer_error_reporter = std::make_shared<Lexer_error_reporter>();
  Lexer lexer {source, lexer_error_reporter};
  auto tokens = lexer.get_tokens();
  if (lexer_error_reporter->had_error()) return;

  auto parser_error_reporter = std::make_shared<Parser_error_reporter>();
  Parser parser {tokens, parser_error_reporter};
  // Parses only first expression if running through file.
  auto expr = parser.parse();
  if (parser_error_reporter->had_error()) return;
  Ast_printer printer;
  printer.print(expr);
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
  run(file_content);
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
