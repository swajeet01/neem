#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "../Token/token.h"

class Lexer {
  std::string msource;

public:
  Lexer(const std::string source):
  msource {source} {}

  std::vector<Token> get_tokens();
};

#endif // !LEXER_H
