#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include <initializer_list>
#include <string>
#include <memory>

#include "Ast/expr.hpp"
#include "mutable_state_visitor.hpp"

class Ast_printer: public Mutable_state_visitor {
  std::string data;
  std::string parenthesize(std::string,
      std::initializer_list<std::shared_ptr<Expr>>);
  void visit(Binary&);
  void visit(Unary&);
  void visit(Grouping&);
  void visit(Ast_literal&);
public:
  std::string print(std::shared_ptr<Expr>);
};


#endif // !AST_PRINTER_H
