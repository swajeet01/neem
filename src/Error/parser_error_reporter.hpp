#ifndef PARSER_ERROR_REPORTER_H
#define PARSER_ERROR_REPORTER_H

#include <memory>
#include <string>

#include "error_reporter.hpp"
#include "Token/token.hpp"

class Parser_error_reporter: public Error_reporter {
  bool fhad_error;
public:
  void error(const Token&, std::string);
  void report(int, std::string, std::string);
  bool had_error();
};

#endif // !PARSER_ERROR_REPORTER_H
