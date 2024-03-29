#ifndef LEXER_H
#define LEXER_H

#include <memory>
#include <string>
#include <vector>

#include "Token/token.hpp"
#include "Error/lexer_error_reporter.hpp"
#include "Variant/literal.hpp"

class Lexer {
  std::string source;
  std::vector<Token> tokens {};
  Lexer_error_reporter& error_reporter;
  size_t start {0};
  size_t current {0};
  size_t line {1};
  char peek();
  char peek_next();
  bool match(char);
  void string_tk();
  void number();
  void identifier();
  void get_token();
  void add_token(Token_type);
  void add_token(Token_type, const Literal&);
  char advance();
public:
  Lexer(std::string , Lexer_error_reporter&);
  bool is_at_end();
  std::vector<Token> get_tokens();
};

#endif // !LEXER_H
