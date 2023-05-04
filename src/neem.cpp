#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "Ast/expr_fwd.h"
#include "Error/error_reporter.h"
#include "Error/lexer_error_reporter.h"
#include "Token/token.h"
#include "Token/token_type.h"
#include "Variant/literal.h"
#include "Visitor/ast_printer.h"
#include "common.h"
#include "Lexer/lexer.h"
#include "Parser/parser.h"

void run(const std::string source) {
  std::shared_ptr<Error_reporter> lexer_error_reporter =
      std::make_shared<Lexer_error_reporter>();
  Lexer lexer {source, lexer_error_reporter};
  auto tokens = lexer.get_tokens();
  for (auto token : tokens) {
    std::cout << token.to_string() << common::newl;
  }
  // Parser parser {tokens};
  // parser.parse();
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
  auto expr = std::make_shared<Binary>(
    std::make_shared<Ast_literal>(
      std::make_shared<Literal>(Literal_type::Number, 10.0)
    ),
    std::make_shared<Token>(std::string {"+"}, 10, Token_type::PLUS, Literal()),
    std::make_shared<Ast_literal>(
      std::make_shared<Literal>(Literal_type::Number, 20.0)
    )
  );
  Ast_printer ast_printer;
  ast_printer.print(expr);
  return 0;
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
