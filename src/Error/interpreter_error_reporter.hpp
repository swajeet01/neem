#ifndef INTERPRETER_ERROR_REPORTER_H
#define INTERPRETER_ERROR_REPORTER_H

#include <string>

#include "Token/token.hpp"
#include "error_reporter.hpp"
#include "neem_runtime_error.hpp"

class Interpreter_error_reporter: public Error_reporter {
  bool fhad_error;
public:
  void error(Neem_runtime_error&);
  void report(int, std::string, std::string);
  bool had_error();
};

#endif // !INTERPRETER_ERROR_REPORTER_H
