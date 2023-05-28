#ifndef PARSER_H
#define PARSER_H

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "../Token/token.h"
#include "../Ast/expr.h"
#include "../Ast/stmt.h"
#include "../Error/parse_error.h"
#include "../Error/parser_error_reporter.h"

class Parser {
  std::vector<Token> tokens;
  size_t current = 0;
  std::shared_ptr<Parser_error_reporter> error_reporter;
  bool match(std::initializer_list<Token_type>);
  std::shared_ptr<Expr> comparison();
  const Token& previous();
  bool check(Token_type);
  const Token& advance();
  const Token& peek();
  bool is_at_end();
  const Token& consume(Token_type, const std::string);
  Parse_error error(const Token&, const std::string message);
  void synchronize();
  std::shared_ptr<Expr> expression();
  std::shared_ptr<Expr> assignment();
  std::shared_ptr<Expr> equality();
  std::shared_ptr<Expr> term();
  std::shared_ptr<Expr> factor();
  std::shared_ptr<Expr> unary();
  std::shared_ptr<Expr> primary();
  std::shared_ptr<Stmt> statement();
  std::shared_ptr<Stmt> print_statement();
  std::shared_ptr<Stmt> expr_statement();
  std::shared_ptr<Stmt> declaration();
  std::shared_ptr<Stmt> var_declaration();
public:
  Parser(const std::vector<Token>&, std::shared_ptr<Parser_error_reporter>);
  std::vector<std::shared_ptr<Stmt>> parse();
};

#endif // !PARSER_H
