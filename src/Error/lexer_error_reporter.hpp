#ifndef LEXER_ERROR_REPORTER_H
#define LEXER_ERROR_REPORTER_H

#include <string>

#include "error_reporter.hpp"

class Lexer_error_reporter: public Error_reporter {
  bool mhad_error;
public:
  void error(size_t, std::string);
  void report(size_t, std::string, std::string) override;
  bool had_error() override;
};

#endif // !LEXER_ERROR_REPORTER_H
