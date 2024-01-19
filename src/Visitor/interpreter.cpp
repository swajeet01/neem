#include <algorithm>
#include <cmath>
#include <memory>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Ast/expr.hpp"
#include "Ast/stmt.hpp"
#include "Callable/neem_function.hpp"
#include "Environment/environment.hpp"
#include "Error/neem_runtime_error.hpp"
#include "Error/interpreter_error_reporter.hpp"
#include "Variant/neem_value.hpp"
#include "Callable/neem_callable.hpp"
#include "Callable/native_functions.hpp"
#include "common.hpp"
#include "interpreter.hpp"

Interpreter::Interpreter(Interpreter_error_reporter& perror_reporter):
    error_reporter {perror_reporter},
    environment {&globals} {

  globals.define(
    "clock",
    Neem_value {Value_type::NEEM_CALLABLE,
    std::make_shared<Clock>()}
  );

  globals.define(
    "str",
    Neem_value {Value_type::NEEM_CALLABLE,
    std::make_shared<Str>()}
  );

  globals.define(
    "read",
    Neem_value {Value_type::NEEM_CALLABLE,
    std::make_shared<Read>()}
  );
}

Interpreter_error_reporter& Interpreter::get_error_reporter() {
  return error_reporter;
}

void check_number_operand(Token& token, Neem_value& operand) {
  if (operand.get_type() == Value_type::NUMBER) return;
  throw Neem_runtime_error {token, "Operand must be a number."};
}

void check_number_operand(Token& token, Neem_value& left, Neem_value& right) {
  if (left.get_type() == Value_type::NUMBER && right.get_type() == Value_type::NUMBER)
    return;
  throw Neem_runtime_error {token, "Operand must be numbers."};
}

void Interpreter::visit(Ast_literal* expr) {
  switch (expr->value.get_type()) {
    case Literal_type::NUMBER:
      data = Neem_value(Value_type::NUMBER, expr->value.get_number());
      break;
    case Literal_type::STRING:
      data = Neem_value(Value_type::STRING, expr->value.get_string());
      break;
    case Literal_type::BOOL:
      data = Neem_value(Value_type::BOOL, expr->value.get_bool());
      break;
    case Literal_type::NIL:
      data = Neem_value();
      break;
  }
}

void Interpreter::visit(Grouping* gexpr) {
  data = evaluate(gexpr->expr);
}

void Interpreter::visit(Unary* expr) {
  Neem_value right = evaluate(expr->right);
  switch (expr->op.type) {
    case Token_type::BANG:
      data = Neem_value {Value_type::BOOL, !is_truthy(right)};
      break;
    case Token_type::MINUS:
      check_number_operand(expr->op, right);
      data = Neem_value {Value_type::NUMBER, -right.get_number()};
      break;
    default:
      // Unreachable in normal circumstances.
    break;
  }
}

void Interpreter::visit(Binary* expr) {
  Neem_value left = evaluate(expr->left);
  Neem_value right = evaluate(expr->right);

  switch (expr->op.type) {
    case Token_type::MINUS:
      check_number_operand(expr->op, left, right);
      data = Neem_value {Value_type::NUMBER, left.get_number() - right.get_number()};
      break;

    case Token_type::SLASH:
      check_number_operand(expr->op, left, right);
      data = Neem_value {Value_type::NUMBER, left.get_number() / right.get_number()};
      break;

    case Token_type::STAR:
      check_number_operand(expr->op, left, right);
      data = Neem_value {Value_type::NUMBER, left.get_number() * right.get_number()};
      break;

    case Token_type::MOD:
      check_number_operand(expr->op, left, right);
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
        throw Neem_runtime_error {expr->op, "Operands must be two number or two strings."};
      }
      break;

    case Token_type::GREATER:
      check_number_operand(expr->op, left, right);
      data = Neem_value {Value_type::BOOL, left.get_number() > right.get_number()};
      break;

    case Token_type::GREATER_EQ:
      check_number_operand(expr->op, left, right);
      data = Neem_value {Value_type::BOOL, left.get_number() >= right.get_number()};
      break;

    case Token_type::LESSER:
      check_number_operand(expr->op, left, right);
      data = Neem_value {Value_type::BOOL, left.get_number() < right.get_number()};
      break;

    case Token_type::LESSER_EQ:
      check_number_operand(expr->op, left, right);
      data = Neem_value {Value_type::BOOL, left.get_number() <= right.get_number()};
      break;

    case Token_type::BANG_EQ:
      data = Neem_value {Value_type::BOOL, !is_equal(left, right)};
      break;

    case Token_type::EQ_EQ:
      data = Neem_value {Value_type::BOOL, is_equal(left, right)};
      break;
    default:
      // Unreachable in normal circumstances.
    break;
  }
}

void Interpreter::visit(Call* expr) {
  Neem_value callee = evaluate(expr->callee);

  if (callee.get_type() != Value_type::NEEM_CALLABLE) {
    throw Neem_runtime_error {expr->paren, "Non function type value called."};
  }

  std::vector<Neem_value> arguments;
  for (auto argument: expr->arguments) {
    arguments.push_back(evaluate(argument));
  }

  std::shared_ptr<Neem_callable> function = callee.get_callable();
  if (arguments.size() != function->arity()) {
    std::ostringstream composer;
    composer << "Expected " << function->arity() << " arguments, "
      "got " << arguments.size() << ".";
    throw Neem_runtime_error(expr->paren, composer.str());
  }
  data = function->call(*this, arguments);
}

Neem_value Interpreter::evaluate(std::shared_ptr<Expr> expr) {
  expr->accept(*this);
  // Neem_value evaluated = data;
  // data.clear();
  // return evaluated;
  return data;
}

bool Interpreter::is_truthy(Neem_value& right) {
  if (right.get_type() == Value_type::NIL) return false;
  if (right.get_type() == Value_type::BOOL) return right.get_bool();
  return true;
}

bool Interpreter::is_equal(Neem_value& left, Neem_value& right) {
  if (left.get_type() == Value_type::NIL &&
      right.get_type() == Value_type::NIL) {
    return true;
  }
  // Reaches here, if both or either one is not nil.
  if (left.get_type() == Value_type::NIL ||
      right.get_type() == Value_type::NIL) {
    return false;
  }
  // Reaches here, if both are not nil.
  if (left.get_type() != right.get_type()) {
    return false;
  }

  switch (left.get_type()) {
    case Value_type::NUMBER:
      return left.get_number() == right.get_number();
    case Value_type::STRING:
      return left.get_string() == right.get_string();
    case Value_type::BOOL:
      return left.get_bool() == right.get_bool();
    default:
      // Unreachable in normal circumstances.
      break;
  }
  return false;
}

void Interpreter::visit(Expression* stmt) {
  evaluate(stmt->expression);
  data = Neem_value {};
}

void Interpreter::visit(Print* stmt) {
  auto value = evaluate(stmt->expression);
  std::cout << value.to_string() << common::newl;
  data = Neem_value {};
}

void Interpreter::visit(Var* stmt) {
  Neem_value value {};
  if (stmt->initializer) {
    value = evaluate(stmt->initializer);
  }
  environment->define(stmt->name.lexeme, value);
  data = Neem_value {};
}

void Interpreter::visit(Variable* expr) {
  data = lookup_variable(expr->name, expr);
}

void Interpreter::visit(Assign* expr) {
  Neem_value value = evaluate(expr->value);
  Locals::iterator itr = locals.find(expr);
  if (itr != locals.end()) {
    int distance = itr->second;
    environment->assign_at(distance, expr->name, value);
  } else {
    globals.assign(expr->name, value);
  }
  data = value;
}

void Interpreter::visit(Logical* expr) {
  auto left = evaluate(expr->left);
  if (expr->op.type == Token_type::OR) {
    if (is_truthy(left)) {
      data = left;
      return;
    }
  } else {
    if (!is_truthy(left)) {
      data = left;
      return;
    }
  }
  data = evaluate(expr->right);
}

void Interpreter::visit(Block* stmt) {
  std::shared_ptr<Environment> local_environment = std::make_shared<Environment>(environment);
  execute_block(stmt->statements, local_environment);
  data = Neem_value();
}

void Interpreter::visit(If* stmt) {
  auto condition_value = evaluate(stmt->condition);
  if (is_truthy(condition_value)) {
    execute(stmt->then_branch);
  } else if (stmt->else_branch) {
    execute(stmt->else_branch);
  }
  data = Neem_value();
}

void Interpreter::visit(While* stmt) {
  auto condition_value = evaluate(stmt->condition);
  while (is_truthy(condition_value)) {
    execute(stmt->body);
    condition_value = evaluate(stmt->condition);
  }
  data = Neem_value();
}

void Interpreter::visit(Function* stmt) {
  auto function_cpy =
    std::make_shared<Function>(stmt->name, stmt->params, stmt->body);
  std::shared_ptr<Neem_function> function =
    std::make_shared<Neem_function>(function_cpy, closure_candidate);
  environment->define(stmt->name.lexeme,
                      Neem_value {Value_type::NEEM_CALLABLE, function});
  data = Neem_value {};
}

void Interpreter::visit(Return* stmt) {
  Neem_value value {};
  if (stmt->value) {
    value = evaluate(stmt->value);
  }
  throw Return_hack {value};
}

void Interpreter::resolve(Expr* expr, int depth) {
  locals[expr] = depth;
}

Neem_value Interpreter::lookup_variable(Token& name, Expr* expr) {
  Locals::iterator itr = locals.find(expr);
  if (itr != locals.end()) {
    int distance = itr->second;
    return environment->get_at(distance, name.lexeme);
  } else {
    return globals.get(name);
  }
}

void Interpreter::execute_block(std::vector<std::shared_ptr<Stmt>>& statements,
                                std::shared_ptr<Environment> p_environment) {
  try {
    Interpreter_env_controller executor {*this, p_environment};
    for (std::shared_ptr<Stmt>& statement: statements) {
      execute(statement);
    }
  } catch (Neem_runtime_error& err) {
    // Did I forget something?
    throw;
  }
}

void Interpreter::execute(std::shared_ptr<Stmt>& statement) {
  statement->accept(*this);
}

void Interpreter::interprete(std::vector<std::shared_ptr<Stmt>>& statements) {
  try {
    for (std::shared_ptr<Stmt>& statement: statements) {
      execute(statement);
    }
  } catch (Neem_runtime_error& err) {
    error_reporter.error(err);
  }
}

Interpreter_env_controller::Interpreter_env_controller(Interpreter& p_interpreter,
                                                       std::shared_ptr<Environment> p_environment):
  interpreter {p_interpreter},
  old_environment {interpreter.environment} {
  interpreter.closure_candidate = p_environment;
  interpreter.environment = p_environment.get();
}

Interpreter_env_controller::~Interpreter_env_controller() {
  interpreter.environment = old_environment;
  interpreter.closure_candidate.reset();
}

