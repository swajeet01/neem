#include <iostream>
#include <string>

#include "../common.h"
#include "neem_runtime_error.h"
#include "interpreter_error_reporter.h"

void Interpreter_error_reporter::report(int line, std::string where,
    std::string message) {
  std::cerr << line << "| Runtime error: " << message << common::newl;
  fhad_error = true;
}

void Interpreter_error_reporter::error(Neem_runtime_error& err) {
  report(err.token.line, "", err.what());
}

bool Interpreter_error_reporter::had_error() {
  return fhad_error;
}
