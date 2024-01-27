#include <iostream>
#include <string>
#include <utility>

#include "common.hpp"
#include "lexer_error_reporter.hpp"

void Lexer_error_reporter::error(size_t line, std::string message) {
  report(line, "", std::move(message));
}

void Lexer_error_reporter::report(size_t line, std::string where,
  std::string message) {
  std::cerr << line << "| Scan error: " << message << common::newl;
  mhad_error = true;
}

bool Lexer_error_reporter::had_error() {
  return mhad_error;
}
