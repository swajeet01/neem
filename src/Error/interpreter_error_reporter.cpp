#include <iostream>
#include <string>

#include "common.hpp"
#include "neem_runtime_error.hpp"
#include "interpreter_error_reporter.hpp"

void Interpreter_error_reporter::report(int line, std::string where,
    std::string message) {
  std::cerr << line << "| Runtime error: " << message << common::newl;
  fhad_error = true;
}

void Interpreter_error_reporter::error(Neem_runtime_error& err) {
  report(err.token.line, "Near token '" + err.token.lexeme + "'.", err.what());
}

bool Interpreter_error_reporter::had_error() {
  return fhad_error;
}
