#include <string>

#include "token.h"
#include "token_type.h"
#include "../common.h"

Token::Token(const std::string plexeme, int pline, Token_type ptype):
    lexeme {plexeme}, line {pline}, type {ptype} { }

std::string Token::to_string() {
  return "Token '" + lexeme + "' ";
}
