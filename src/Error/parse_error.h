#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include <stdexcept>
#include <string>

struct Parse_error: public std::runtime_error {
  Parse_error(const std::string);
};

#endif // !PARSE_ERROR_H
