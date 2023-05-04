#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include <string>

#include "token_type.h"
#include "../Variant/literal.h"

class Token {
  int line;
  Token_type type;
  std::shared_ptr<Literal> literal;
public:
  std::string lexeme;
  Token(const std::string, int, Token_type, std::shared_ptr<Literal>);
  std::string to_string();
};

#endif // !TOKEN_H
