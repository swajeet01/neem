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
  Neem_value data;
  bool is_truthy(Neem_value&);
  bool is_equal(Neem_value& left, Neem_value& right);
  void visit(Binary&);
  void visit(Call&);
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
  void visit(Function&);
  void visit(Return&);
  Neem_value evaluate(std::shared_ptr<Expr>);
  void execute(std::shared_ptr<Stmt>);
public:
  Interpreter(Interpreter_error_reporter&);
  std::shared_ptr<Environment> globals;
  std::shared_ptr<Environment> environment;
  void execute_block(std::vector<std::shared_ptr<Stmt>>&,
      std::shared_ptr<Environment>);
  void interprete(std::vector<std::shared_ptr<Stmt>>);
  Interpreter_error_reporter& get_error_reporter();
};

struct Interpreter_env_controller {
  Interpreter& interpreter;
  std::shared_ptr<Environment> old_environment;
  std::shared_ptr<Environment> new_environment;
  Interpreter_env_controller(Interpreter&, std::shared_ptr<Environment>);
  ~Interpreter_env_controller();
};

struct Return_hack {
  Neem_value value;
};

#endif // !INTERPRETER_H
