#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
  std::string lexeme;
  int line;
public:
  Token(const std::string, int);
};

#endif // !TOKEN_H
