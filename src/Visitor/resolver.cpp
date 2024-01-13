#include <memory>
#include <vector>
#include <iostream>

#include "Ast/expr.hpp"
#include "Ast/stmt.hpp"
#include "Error/neem_runtime_error.hpp"
#include "Token/token.hpp"
#include "Visitor/interpreter.hpp"
#include "Visitor/resolver.hpp"

Resolver::Resolver(Interpreter& p_interpreter):
  interpreter {p_interpreter} { }

void Resolver::resolve(std::vector<std::shared_ptr<Stmt>>& statements) {
  for (std::shared_ptr<Stmt>& statement: statements) {
    resolve(statement);
  }
}

void Resolver::resolve(std::shared_ptr<Stmt>& stmt) {
  stmt->accept(*this);
}

void Resolver::resolve(std::shared_ptr<Expr>& expr) {
  expr->accept(*this);
}

void Resolver::begin_scope() {
  scopes.emplace_back();
}

void Resolver::end_scope() {
  scopes.pop_back();
}

void Resolver::declare(Token& name) {
  if (scopes.empty()) {
    return;
  }
  Map& scope = scopes.back();
  if (scope.find(name.lexeme) != scope.end()) {
    Neem_runtime_error error {name, 
      "Redefinition of variable in local scope."};
    interpreter.get_error_reporter().error(error);
  }
  scope[name.lexeme] = false;
}

void Resolver::define(Token& name) {
  if (scopes.empty()) {
    return;
  }
  Map& scope = scopes.back();
  scope[name.lexeme] = true;
}

void Resolver::resolve_local(Expr* expr, Token& name) {
  for (int i = scopes.size() - 1; i >= 0; i--) {
    Map& scope = scopes[i];
    Map::iterator itr = scope.find(name.lexeme);
    if (itr != scope.end()) {
      interpreter.resolve(expr, scopes.size() - 1 - i);
      return;
    }
  }
}

void Resolver::resolve_function(Function* function, Function_type type) {
  Function_type enclosing_function = current_function;
  current_function = type;
  begin_scope();
  for (Token& param: function->params) {
    declare(param);
    define(param);
  }
  resolve(function->body);
  end_scope();
  current_function = enclosing_function;
}

void Resolver::visit(Block* stmt) {
  begin_scope();
  resolve(stmt->statements);
  end_scope();
}

void Resolver::visit(Function* stmt) {
  declare(stmt->name);
  define(stmt->name);
  resolve_function(stmt, Function_type::FUNCTION);
}

void Resolver::visit(Var* stmt) {
  declare(stmt->name);
  if (stmt->initializer) {
    resolve(stmt->initializer);
  }
  define(stmt->name);
}

void Resolver::visit(Assign* expr) {
  resolve(expr->value);
  resolve_local(expr, expr->name);
}

void Resolver::visit(Variable* expr) {
  if (!scopes.empty()) {
    // scopes.back().at(expr->name.lexeme) == false)
    Map& scope = scopes.back();
    Map::iterator itr = scope.find(expr->name.lexeme); 
    if ((itr != scope.end()) && itr->second == false) {
      Neem_runtime_error error {expr->name,
        "Can't read local variable in its own initializer."};
      interpreter.get_error_reporter().error(error);
    }
  }
  resolve_local(expr, expr->name);
}

void Resolver::visit(Expression* stmt) {
  resolve(stmt->expression);
}

void Resolver::visit(If* stmt) {
  resolve(stmt->condition);
  resolve(stmt->then_branch);
  if (stmt->else_branch) {
    resolve(stmt->else_branch);
  }
}

void Resolver::visit(Print* stmt) {
  resolve(stmt->expression);
}

void Resolver::visit(Return* stmt) {
  if (current_function == Function_type::NONE) {
    Neem_runtime_error error {stmt->keyword,
      "Return statment not allowed at top-level."};
    interpreter.get_error_reporter().error(error);
  }
  if (stmt->value) {
    resolve(stmt->value);
  }
}

void Resolver::visit(While* stmt) {
  resolve(stmt->condition);
  resolve(stmt->body);
}

void Resolver::visit(Binary* expr) {
  resolve(expr->left);
  resolve(expr->right);
}

void Resolver::visit(Call* expr) {
  resolve(expr->callee);
  for (std::shared_ptr<Expr>& argument: expr->arguments) {
    resolve(argument);
  }
}

void Resolver::visit(Grouping* expr) {
  resolve(expr->expr);
}

void Resolver::visit(Ast_literal* expr) { }

void Resolver::visit(Logical* expr) {
  resolve(expr->left);
  resolve(expr->right);
}

void Resolver::visit(Unary* expr) {
  resolve(expr->right);
}
