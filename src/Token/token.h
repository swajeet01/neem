#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"
#include <string>

class Token {
  std::string lexeme;
  int line;
  Token_type type;
public:
  Token(const std::string, int, Token_type);
  std::string to_string();
};

#endif // !TOKEN_H
