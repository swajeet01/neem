#include <iostream>
#include <string>

#include "../common.h"
#include "lexer_error_reporter.h"

void Lexer_error_reporter::error(int line, std::string message) {
  // TODO: Generate location
  report(line, "", message);
}

void Lexer_error_reporter::report(int line, std::string where,
    std::string message) {
  // Temp message
  std::cout << line << " Error: " << message << common::newl;
}

bool Lexer_error_reporter::had_error() {
  return fhad_error;
}
