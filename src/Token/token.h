#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include <string>

#include "token_type.h"
#include "../Variant/literal.h"

class Token {
public:
  Token(const std::string, int, Token_type, std::shared_ptr<Literal>);
  int line;
  std::shared_ptr<Literal> literal;
  Token_type type;
  std::string lexeme;
  std::string to_string();
};

#endif // !TOKEN_H
