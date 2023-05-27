#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <vector>

#include "../Ast/expr.h"
#include "../Ast/stmt.h"
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
  void visit(Expression&);
  void visit(Print&);
  Neem_value evaluate(std::shared_ptr<Expr>);
  void execute(std::shared_ptr<Stmt>);
public:
  void interprete(std::vector<std::shared_ptr<Stmt>>);
  Interpreter(std::shared_ptr<Interpreter_error_reporter>);
};

#endif // !INTERPRETER_H
