#include <iostream>
#include <string>

#include "../common.h"
#include "lexer_error_reporter.h"

void Lexer_error_reporter::error(int line, std::string message) {
  report(line, "", message);
}

void Lexer_error_reporter::report(int line, std::string where,
  std::string message) {
  std::cerr << line << "| Scan error: " << message << common::newl;
  fhad_error = true;
}

bool Lexer_error_reporter::had_error() {
  return fhad_error;
}
