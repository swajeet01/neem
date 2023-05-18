#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>

#include "../Ast/expr.h"
#include "../Variant/neem_value.h"
#include "mutable_state_visitor.h"
#include "../Error/interpreter_error_reporter.h"

class Interpreter: public Mutable_state_visitor {
  std::shared_ptr<Interpreter_error_reporter> error_reporter;
  Neem_value data;
  bool is_truthy(Neem_value&);
  bool is_equal(Neem_value& left, Neem_value& right);
  void visit(Binary&);
  void visit(Unary&);
  void visit(Grouping&);
  void visit(Ast_literal&);
  Neem_value evaluate(std::shared_ptr<Expr>);
public:
  void interprete(std::shared_ptr<Expr>);
  Interpreter(std::shared_ptr<Interpreter_error_reporter>);
};

#endif // !INTERPRETER_H
