#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include <string>

#include "token_type.hpp"
#include "Variant/literal.hpp"

class Token {
public:
  Token(std::string , int, Token_type, Literal);
  int line;
  Literal literal;
  Token_type type;
  std::string lexeme;
  std::string to_string();
};

#endif // !TOKEN_H
