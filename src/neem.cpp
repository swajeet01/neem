#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "Error/error_reporter.h"
#include "Error/lexer_error_reporter.h"
#include "common.h"
#include "Lexer/lexer.h"
#include "Parser/parser.h"

void run(const std::string source) {

  std::shared_ptr<Error_reporter> lexer_error_reporter =
      std::make_shared<Lexer_error_reporter>();
  Lexer lexer {source, lexer_error_reporter};
  auto tokens = lexer.get_tokens();
  for (auto token: tokens) {
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
