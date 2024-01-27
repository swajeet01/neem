#include <string>
#include <utility>

#include "token_type.hpp"
#include "Variant/literal.hpp"
#include "token.hpp"

Token::Token(std::string  plexeme, int pline, Token_type ptype,
    Literal pliteral):
    lexeme {std::move(plexeme)}, line {pline}, type {ptype}, literal {std::move(pliteral)} { }

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
