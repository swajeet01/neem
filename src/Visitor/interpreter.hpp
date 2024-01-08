#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <vector>

#include "Ast/expr.hpp"
#include "Ast/stmt.hpp"
#include "Environment/environment.hpp"
#include "Variant/neem_value.hpp"
#include "mutable_state_visitor.hpp"
#include "Error/interpreter_error_reporter.hpp"

class Interpreter: public Mutable_state_visitor {
  Interpreter_error_reporter& error_reporter;
  std::shared_ptr<Environment>  environment;
  Neem_value data;
  bool is_truthy(Neem_value&);
  bool is_equal(Neem_value& left, Neem_value& right);
  void visit(Binary&);
  void visit(Unary&);
  void visit(Grouping&);
  void visit(Ast_literal&);
  void visit(Expression&);
  void visit(Print&);
  void visit(Var&);
  void visit(Variable&);
  void visit(Assign&);
  void visit(Block&);
  void visit(If&);
  void visit(Logical&);
  void visit(While&);
  Neem_value evaluate(std::shared_ptr<Expr>);
  void execute_block(std::vector<std::shared_ptr<Stmt>>&,
      std::shared_ptr<Environment>);
  void execute(std::shared_ptr<Stmt>);
public:
  Interpreter(Interpreter_error_reporter&);
  void interprete(std::vector<std::shared_ptr<Stmt>>);
  Interpreter_error_reporter& get_error_reporter();
};

#endif // !INTERPRETER_H
