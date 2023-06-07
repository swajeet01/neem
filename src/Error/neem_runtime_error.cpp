#include <stdexcept>
#include <string>

#include "../Token/token.hpp"
#include "neem_runtime_error.hpp"

Neem_runtime_error::Neem_runtime_error(Token ptoken, std::string message):
  token {ptoken.lexeme, ptoken.line, ptoken.type, ptoken.literal }, std::runtime_error {message} {}
