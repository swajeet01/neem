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
  data = "Binary";
}

void Ast_printer::visit(Unary& expr) {
  data = "Unary";
}

void Ast_printer::visit(Grouping& expr) {
  data = "Grouping";
}

void Ast_printer::visit(Ast_literal& expr) {
  data = "Ast_literal";
}
