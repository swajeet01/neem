#ifndef NEEM_RUNTIME_ERROR_H
#define NEEM_RUNTIME_ERROR_H

#include <stdexcept>
#include <string>

#include "Token/token.hpp"

struct Neem_runtime_error: public std::runtime_error {
  Token token;
  Neem_runtime_error(const Token&, const std::string&);
};

#endif // !NEEM_RUNTIME_ERROR_H
