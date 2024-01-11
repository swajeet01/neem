#include <memory>
#include <string>

#include "common.hpp"
#include "token_type.hpp"
#include "Variant/literal.hpp"
#include "token.hpp"

Token::Token(const std::string plexeme, int pline, Token_type ptype,
    Literal pliteral):
    lexeme {plexeme}, line {pline}, type {ptype}, literal {pliteral} { }

std::string Token::to_string() {
  auto str = "Token '" + lexeme + "' ";

  switch (literal.get_type()) {
    case Literal_type::NUMBER:
      str = str + std::to_string(literal.get_number());
      break;
    case Literal_type::STRING:
      str = str + literal.get_string();
      break;
    default: break;
  }

  return str;
}
