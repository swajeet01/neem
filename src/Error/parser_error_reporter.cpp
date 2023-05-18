#include <iostream>
#include <memory>
#include <string>

#include "../common.h"
#include "parser_error_reporter.h"


bool Parser_error_reporter::had_error() {
  return fhad_error;
}

void Parser_error_reporter::error(const Token& token,
    std::string message) {
  if (token.type == Token_type::NEOF) {
    report(token.line, " at end", message);
  } else {
    report(token.line, " at '" + token.lexeme + "'", message);
  }
}

void Parser_error_reporter::report(int line, std::string where,
      std::string message) {
  std::cerr << line << "| Parse error: " << message << common::newl <<
      where << common::newl;
  fhad_error = true;
}
