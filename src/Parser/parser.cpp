#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "../Token/token.h"
#include "../Ast/expr.h"
#include "../Ast/stmt.h"
#include "parser.h"

Parser::Parser(const std::vector<Token>& p_tokens,
    std::shared_ptr<Parser_error_reporter> p_error_reporter):
  tokens { p_tokens }, error_reporter {p_error_reporter} {}

const Token& Parser::previous() {
  return tokens[current - 1];
}

const Token& Parser::peek() {
  return tokens[current];
}

bool Parser::is_at_end() {
  return peek().type == Token_type::NEOF;
}

bool Parser::check(Token_type type) {
  if (is_at_end()) return false;
  return peek().type == type;
}

const Token& Parser::advance() {
  if (!is_at_end()) current++;
  return previous();
}

bool Parser::match(std::initializer_list<Token_type> types) {
  for (auto type: types) {
    if (check(type)) {
      advance();
      return true;
    }
  }
  return false;
}

void Parser::synchronize() {
  advance();

  while (!is_at_end()) {
    if (previous().type == Token_type::SEMI_COL) return;

    switch (peek().type) {
      case Token_type::STRUCT:
      case Token_type::FN:
      case Token_type::LET:
      case Token_type::FOR:
      case Token_type::IF:
      case Token_type::WHILE:
      case Token_type::PRINT:
      case Token_type::RETURN:
      return;
    }

    advance();

  }
}

Parse_error Parser::error(const Token& token,
    const std::string message) {
  error_reporter->error(token, message);
  return Parse_error {"Parse error."};
}

const Token& Parser::consume(Token_type type,
    const std::string message) {
  if (check(type)) return advance();
  throw error(peek(), message);
}

std::shared_ptr<Expr> Parser::primary() {
  if (match({Token_type::NTRUE})) {
    return std::make_shared<Ast_literal>(
      Literal{Literal_type::BOOL, true}
    );
  }

  if (match({Token_type::NFALSE})) {
    return std::make_shared<Ast_literal>(
      Literal {Literal_type::BOOL, false}
    );
  }

  if (match({Token_type::NIL}))
    return std::make_shared<Ast_literal>(
      Literal {Literal_type::NIL}
    );
  
  if (match({Token_type::NUMBER, Token_type::STRING})) {
    return std::make_shared<Ast_literal>(
      previous().literal
    );
  }

  if (match({Token_type::LEFT_PAREN})) {
    auto expr = expression();
    consume(Token_type::RIGHT_PAREN, "Expected ')' after expression.");
    return std::make_shared<Grouping>(expr);
  }

  throw error(peek(), "Expect expression.");
}

std::shared_ptr<Expr> Parser::unary() {
  while (match({Token_type::BANG, Token_type::MINUS})) {
    auto op = previous();
    auto right = unary();
    return std::make_shared<Unary>(op, right);
  }
  return primary();
}

std::shared_ptr<Expr> Parser::factor() {
  auto expr = unary();

  while (match({Token_type::SLASH, Token_type::STAR, Token_type::MOD})) {
    auto op = previous();
    auto right = unary();
    expr = std::make_shared<Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::term() {
  auto expr = factor();

  while (match({Token_type::MINUS, Token_type::PLUS})) {
    auto op = previous();
    auto right = term();
    expr = std::make_shared<Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::comparison() {
  auto expr = term();

  while (match({Token_type::GREATER, Token_type::GREATER_EQ,
     Token_type::LESSER, Token_type::LESSER_EQ})) {
    auto op = previous();
    auto right = term();
    expr = std::make_shared<Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::equality() {
  auto expr = comparison();

  while (match({Token_type::BANG_EQ, Token_type::EQ_EQ})) {
    auto op = previous();
    auto right = comparison();
    expr = std::make_shared<Binary>(expr, op, right);
  }

  return expr;
}

std::shared_ptr<Expr> Parser::expression() {
  return equality();
}

std::shared_ptr<Stmt> Parser::statement() {
  if (match({Token_type::PRINT})) {
    return print_statement();
  }
  return expr_statement();
}

std::shared_ptr<Stmt> Parser::print_statement() {
  auto value = expression();
  consume(Token_type::SEMI_COL, "Expected ';' after value.");
  return std::make_shared<Print>(value);
}

std::shared_ptr<Stmt> Parser::expr_statement() {
  auto expr = expression();
  consume(Token_type::SEMI_COL, "Expected ';' after expression.");
  return std::make_shared<Expression>(expr);
}

std::vector<std::shared_ptr<Stmt>> Parser::parse() {
  try {
    std::vector<std::shared_ptr<Stmt>> statements;
    while (!is_at_end()) {
      statements.push_back(statement());
    }
    return statements;
  } catch (Parse_error& e) {}
  return {};
}
