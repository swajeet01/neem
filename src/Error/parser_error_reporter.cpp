#include <iostream>
#include <string>

#include "common.hpp"
#include "parser_error_reporter.hpp"


bool Parser_error_reporter::had_error() {
  return mhad_error;
}

void Parser_error_reporter::error(const Token& token,
    const std::string& message) {
  if (token.type == Token_type::NEOF) {
    report(token.line, " at end", message);
  } else {
    report(token.line, " at '" + token.lexeme + "'", message);
  }
}

void Parser_error_reporter::report(size_t line, std::string where,
      std::string message) {
  std::cerr << line << "| Parse error: " << message << common::newl <<
      where << common::newl;
  mhad_error = true;
}
