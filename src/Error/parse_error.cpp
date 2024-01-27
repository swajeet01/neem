#include <stdexcept>
#include <string>

#include "parse_error.hpp"

Parse_error::Parse_error(const std::string& p_message):
  std::runtime_error{p_message} {}
