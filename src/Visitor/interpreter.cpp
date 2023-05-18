#include <cmath>
#include <memory>
#include <iostream>

#include "../Ast/expr.h"
#include "../Error/neem_runtime_error.h"
#include "../Error/interpreter_error_reporter.h"
#include "../common.h"
#include "interpreter.h"

void check_number_operand(Token& token, Neem_value& operand) {
  if (operand.get_type() == Value_type::NUMBER) return;
  throw Neem_runtime_error {token, "Operand must be a number."};
}

void check_number_operand(Token& token, Neem_value& left, Neem_value& right) {
  if (left.get_type() == Value_type::NUMBER && right.get_type() == Value_type::NUMBER)
    return;
  throw Neem_runtime_error {token, "Operand must be numbers"};
}

Interpreter::Interpreter(std::shared_ptr<Interpreter_error_reporter> perror_reporter):
  error_reporter {perror_reporter} {}

void Interpreter::visit(Ast_literal& expr) {
  switch (expr.value.get_type()) {
    case Literal_type::NUMBER:
      data = Neem_value(Value_type::NUMBER, expr.value.get_number());
      break;
    case Literal_type::STRING:
      data = Neem_value(Value_type::STRING, expr.value.get_string());
      break;
    case Literal_type::BOOL:
      data = Neem_value(Value_type::BOOL, expr.value.get_bool());
      break;
    case Literal_type::NIL:
      data = Neem_value();
      break;
  }
}

void Interpreter::visit(Grouping& gexpr) {
  data = evaluate(gexpr.expr);
}

void Interpreter::visit(Unary& expr) {
  Neem_value right = evaluate(expr.right);
  switch (expr.op.type) {
    case Token_type::BANG:
      data = Neem_value {Value_type::BOOL, !is_truthy(right)};
      break;
    case Token_type::MINUS:
      check_number_operand(expr.op, right);
      data = Neem_value {Value_type::NUMBER, -right.get_number()};
      break;
  }
}

void Interpreter::visit(Binary& expr) {
  Neem_value left = evaluate(expr.left);
  Neem_value right = evaluate(expr.right);

  switch (expr.op.type) {

    case Token_type::MINUS:
      check_number_operand(expr.op, left, right);
      data = Neem_value {Value_type::NUMBER, left.get_number() - right.get_number()};
      break;

    case Token_type::SLASH:
      check_number_operand(expr.op, left, right);
      data = Neem_value {Value_type::NUMBER, left.get_number() / right.get_number()};
      break;

    case Token_type::STAR:
      check_number_operand(expr.op, left, right);
      data = Neem_value {Value_type::NUMBER, left.get_number() * right.get_number()};
      break;

    case Token_type::MOD:
      check_number_operand(expr.op, left, right);
      data = Neem_value {Value_type::NUMBER, std::fmod(left.get_number(), right.get_number())};
      break;

    case Token_type::PLUS:
      if (left.get_type() == Value_type::NUMBER && right.get_type() == Value_type::NUMBER) {
        data = Neem_value {Value_type::NUMBER, left.get_number() + right.get_number()};
      }
      else if (left.get_type() == Value_type::STRING && right.get_type() == Value_type::STRING) {
        data = Neem_value {Value_type::STRING, left.get_string() + right.get_string()};
      }
      else {
        throw Neem_runtime_error {expr.op, "Operands must be two number or two strings."};
      }
      break;

    case Token_type::GREATER:
      check_number_operand(expr.op, left, right);
      data = Neem_value {Value_type::BOOL, left.get_number() > right.get_number()};
      break;

    case Token_type::GREATER_EQ:
      check_number_operand(expr.op, left, right);
      data = Neem_value {Value_type::BOOL, left.get_number() >= right.get_number()};
      break;

    case Token_type::LESSER:
      check_number_operand(expr.op, left, right);
      data = Neem_value {Value_type::BOOL, left.get_number() < right.get_number()};
      break;

    case Token_type::LESSER_EQ:
      check_number_operand(expr.op, left, right);
      data = Neem_value {Value_type::BOOL, left.get_number() <= right.get_number()};
      break;

    case Token_type::BANG_EQ:
      data = Neem_value {Value_type::BOOL, !is_equal(left, right)};
      break;

    case Token_type::EQ_EQ:
      data = Neem_value {Value_type::BOOL, is_equal(left, right)};
      break;
  }
}

Neem_value Interpreter::evaluate(std::shared_ptr<Expr> expr) {
  expr->accept(*this);
  return data;
}

bool Interpreter::is_truthy(Neem_value& right) {
  if (right.get_type() == Value_type::NIL) return false;
  if (right.get_type() == Value_type::BOOL) return right.get_bool();
  return true;
}

bool Interpreter::is_equal(Neem_value& left, Neem_value& right) {
  switch (left.get_type()) {
    case Value_type::NIL:
      return right.get_type() == Value_type::NIL;
    case Value_type::NUMBER:
      return left.get_number() == right.get_number();
    case Value_type::STRING:
      return left.get_string() == right.get_string();
    case Value_type::BOOL:
      return left.get_bool() == right.get_bool();
  }
  return false;
}

void Interpreter::interprete(std::shared_ptr<Expr> expr) {
  try {
    auto value = evaluate(expr);
    std::cout << value.to_string() << common::newl;
  } catch (Neem_runtime_error err) {
    error_reporter->error(err);
  }
}