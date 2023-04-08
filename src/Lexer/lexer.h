#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "../Token/token.h"

class Lexer {
  std::string source;
  std::vector<Token> tokens {};
  size_t start {0};
  size_t current {0};
  size_t line {1};
  void get_token();
  void add_token(Token_type);
  void add_token(Token_type, int); // Temporary param int
  char advance();
public:
  Lexer(const std::string);
  bool is_at_end();
  std::vector<Token> get_tokens();
};

#endif // !LEXER_H
