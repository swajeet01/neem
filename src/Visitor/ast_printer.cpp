#include <iostream>
#include <memory>
#include <string>

#include "../Ast/expr.h"
#include "ast_printer.h"

std::string Ast_printer::print(std::shared_ptr<Expr> expr) {
  expr->accept(*this);
  std::cout << data << "\n";
  return data;
}

void Ast_printer::visit(Binary& expr) {
  data = parenthesize(expr.op->lexeme, { expr.left, expr.right });
}

void Ast_printer::visit(Unary& expr) {
  data = parenthesize(expr.op->lexeme, { expr.right });
}

void Ast_printer::visit(Grouping& expr) {
  data = parenthesize("group", { expr.expr });
}

void Ast_printer::visit(Ast_literal& expr) {
  data = expr.value->to_string();
}

std::string Ast_printer::parenthesize(std::string name,
    std::initializer_list<std::shared_ptr<Expr>> exprs) {
  std::string builder;
  builder.push_back('(');
  builder.append(name);
  for (auto expr: exprs) {
    builder.push_back(' ');
    expr->accept(*this);
    auto result = this->data;
    builder.append(data);
  }
  builder.push_back(')');
  return builder;
}
