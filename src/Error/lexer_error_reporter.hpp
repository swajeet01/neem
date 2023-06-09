#ifndef LEXER_ERROR_REPORTER_H
#define LEXER_ERROR_REPORTER_H

#include <string>

#include "error_reporter.hpp"

class Lexer_error_reporter: public Error_reporter {
  bool fhad_error;
public:
  void error(int, std::string);
  void report(int, std::string, std::string);
  bool had_error();
};

#endif // !LEXER_ERROR_REPORTER_H
