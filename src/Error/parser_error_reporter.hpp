#ifndef PARSER_ERROR_REPORTER_H
#define PARSER_ERROR_REPORTER_H

#include <memory>
#include <string>

#include "error_reporter.hpp"
#include "Token/token.hpp"

class Parser_error_reporter: public Error_reporter {
  bool mhad_error;
public:
  void error(const Token&, const std::string&);
  void report(size_t, std::string, std::string) override;
  bool had_error() override;
};

#endif // !PARSER_ERROR_REPORTER_H
