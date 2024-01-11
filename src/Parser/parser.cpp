#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "Token/token.hpp"
#include "Ast/expr.hpp"
#include "Ast/stmt.hpp"
#include "Token/token_type.hpp"
#include "parser.hpp"

Parser::Parser(const std::vector<Token>& p_tokens,
    Parser_error_reporter& p_error_reporter):
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
  error_reporter.error(token, message);
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

  if (match({Token_type::NIL})) {
    return std::make_shared<Ast_literal>(
      Literal {Literal_type::NIL}
    );
  }
  
  if (match({Token_type::NUMBER, Token_type::STRING})) {
    return std::make_shared<Ast_literal>(
      previous().literal
    );
  }

  if (match({Token_type::IDENTIFIER})) {
    return std::make_shared<Variable>(previous());
  }

  if (match({Token_type::LEFT_PAREN})) {
    auto expr = expression();
    consume(Token_type::RIGHT_PAREN, "Expected ')' after expression.");
    return std::make_shared<Grouping>(expr);
  }

  throw error(peek(), "Expect expression.");
}

std::shared_ptr<Expr> Parser::finish_call(std::shared_ptr<Expr> callee) {
  std::vector<std::shared_ptr<Expr>> arguments;
  if (!check(Token_type::RIGHT_PAREN)) {
    do {
      if (arguments.size() >= 255) {
        error(peek(),
              "Can't have more than 255 arguments."); // Just because bob added.
      }
      arguments.push_back(expression());
    } while (match({Token_type::COMMA}));
  }
  Token paren = consume(Token_type::RIGHT_PAREN,
                        "Expected ')' after arguments.");
  return std::make_shared<Call>(callee, paren, arguments);
}

std::shared_ptr<Expr> Parser::call() {
  std::shared_ptr<Expr> expr = primary();
  while (true) {
    if (match({Token_type::LEFT_PAREN})) {
      expr = finish_call(expr);
    } else {
      break; // for object properties.
    }
  }
  return expr;
}

std::shared_ptr<Expr> Parser::unary() {
  while (match({Token_type::BANG, Token_type::MINUS})) {
    auto op = previous();
    auto right = unary();
    return std::make_shared<Unary>(op, right);
  }
  return call();
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

std::shared_ptr<Expr> Parser::assignment() {
  auto expr = logical_or();
  if (match({Token_type::EQ})) {
    Token equals = previous();
    auto value = assignment();
    // expr must be of type Variable
    // if (variable != nullptr)
    if (auto variable = std::dynamic_pointer_cast<Variable>(expr)) {
      Token name = variable->name;
      return std::make_shared<Assign>(name, value);
    }

    error(equals, "Invalid assignment target.");
  }
  return expr;
}

std::shared_ptr<Expr> Parser::expression() {
  return assignment();
}

std::shared_ptr<Expr> Parser::logical_or() {
  auto expr = logical_and();
  while (match({Token_type::OR})) {
    auto op = previous();
    auto right = logical_and();
    expr = std::make_shared<Logical>(expr, op, right);
  }
  return expr;
}

std::shared_ptr<Expr> Parser::logical_and() {
  auto expr = equality();
  while (match({Token_type::AND})) {
    auto op = previous();
    auto right = equality();
    expr = std::make_shared<Logical>(expr, op, right);
  }
  return expr;
}

std::shared_ptr<Stmt> Parser::statement() {
  if (match({Token_type::FOR})) {
    return for_statement();
  }
  if (match({Token_type::IF})) {
    return if_statement();
  }
  if (match({Token_type::PRINT})) {
    return print_statement();
  }
  if (match({Token_type::WHILE})) {
    return while_statement();
  }
  if (match({Token_type::LEFT_BRACE})) {
    return std::make_shared<Block>(block_statement());
  }
  return expr_statement();
}

std::shared_ptr<Stmt> Parser::if_statement() {
  consume(Token_type::LEFT_PAREN, "Expected '(' after 'if'.");
  auto condition = expression();
  consume(Token_type::RIGHT_PAREN, "Expected ')' after if condition.");
  auto then_branch = statement();
  auto else_branch = std::shared_ptr<Stmt> {};
  if (match({Token_type::ELSE})) {
    else_branch = statement();
  }
  return std::make_shared<If>(condition, then_branch, else_branch);
}

std::shared_ptr<Stmt> Parser::while_statement() {
  consume(Token_type::LEFT_PAREN, "Expected '(' after 'while'.");
  auto condition = expression();
  consume(Token_type::RIGHT_PAREN, "Expected ')' after while condition.");
  auto body = statement();
  return std::make_shared<While>(condition, body);
}

std::shared_ptr<Stmt> Parser::for_statement() {

  consume(Token_type::LEFT_PAREN, "Expected '(' after 'for'.");
  auto initializer = std::shared_ptr<Stmt> {};
  if (match({Token_type::SEMI_COL})) {
    // Do nothing.
    // initializer = nullptr
  } else if (match({Token_type::LET})) {
    initializer = var_declaration();
  } else {
    initializer = expr_statement();
  }

  auto condition = std::shared_ptr<Expr> {};
  if (!check(Token_type::SEMI_COL)) {
    condition = expression();
  }
  consume(Token_type::SEMI_COL, "Expected ';' after loop condition.");

  auto increment = std::shared_ptr<Expr> {};
  if (!check(Token_type::RIGHT_PAREN)) {
    increment = expression();
  }
  consume(Token_type::RIGHT_PAREN, "Expected ')' after loop clauses.");

  auto body = statement();

  if (increment) {
    std::vector<std::shared_ptr<Stmt>> new_body {body, std::make_shared<Expression>(increment)};
    body = std::make_shared<Block>(new_body);
  }

  if (!condition) {
    condition = std::make_shared<Ast_literal>(Literal {Literal_type::BOOL, true});
  }

  body = std::make_shared<While>(condition, body);

  if (initializer) {
    std::vector<std::shared_ptr<Stmt>> new_body {initializer, body};
    body = std::make_shared<Block>(new_body);
  }

  return body;
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

std::vector<std::shared_ptr<Stmt>> Parser::block_statement() {
  std::vector<std::shared_ptr<Stmt>> statements;
  while (!check(Token_type::RIGHT_BRACE) && !is_at_end()) {
    statements.push_back(declaration());
  }
  consume(Token_type::RIGHT_BRACE, "Expected '}' after block.");
  return statements;
}

std::shared_ptr<Stmt> Parser::declaration() {
  try {
    if (match({Token_type::LET})) return var_declaration();
    return statement();
  } catch (Parse_error& err) {
    synchronize();
    return nullptr;
  }
}

std::shared_ptr<Stmt> Parser::var_declaration() {
  auto name = consume(Token_type::IDENTIFIER, "Expected variable name.");
  std::shared_ptr<Expr> initializer;
  if (match({Token_type::EQ})) {
    initializer = expression();
  }
  consume(Token_type::SEMI_COL, "Expected ';' after variable declaration.");
  return std::make_shared<Var>(name, initializer);
}

std::vector<std::shared_ptr<Stmt>> Parser::parse() {
  try {
    std::vector<std::shared_ptr<Stmt>> statements;
    while (!is_at_end()) {
      statements.push_back(declaration());
    }
    return statements;
  } catch (Parse_error& e) {}
  return {};
}
