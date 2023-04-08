#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "../Token/token.h"

class Lexer {
  std::string source;

public:
  Lexer(const std::string);
  std::vector<Token> get_tokens();
};

#endif // !LEXER_H
