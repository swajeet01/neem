#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "Ast/expr.hpp"
#include "Ast/stmt.hpp"
#include "Environment/environment.hpp"
#include "Variant/neem_value.hpp"
#include "mutable_state_visitor.hpp"
#include "Error/interpreter_error_reporter.hpp"

class Interpreter: public Mutable_state_visitor {
public:
  Interpreter(Interpreter_error_reporter&);
  Environment globals;
  Environment* environment;
  std::shared_ptr<Environment> closure_candidate;
  void execute_block(std::vector<std::shared_ptr<Stmt>>&, std::shared_ptr<Environment>);
  using Locals = std::unordered_map<Expr*, int>;
  void interprete(std::vector<std::shared_ptr<Stmt>>&);
  Interpreter_error_reporter& get_error_reporter();
  void resolve(Expr*, int);
private:
  Interpreter_error_reporter& error_reporter;
  Locals locals;
  Neem_value data;
  bool is_truthy(Neem_value&);
  bool is_equal(Neem_value&, Neem_value&);
  void visit(Binary*) override;
  void visit(Call*) override;
  void visit(Unary*) override;
  void visit(Grouping*) override;
  void visit(Ast_literal*) override;
  void visit(Print*) override;
  void visit(Expression*) override;
  void visit(Var*) override;
  void visit(Variable*) override;
  void visit(Assign*) override;
  void visit(Block*) override;
  void visit(If*) override;
  void visit(Logical*) override;
  void visit(While*) override;
  void visit(Function*) override;
  void visit(Return*) override;
  Neem_value evaluate(std::shared_ptr<Expr>);
  void execute(std::shared_ptr<Stmt>&);
  Neem_value lookup_variable(Token&, Expr*);
};

struct Interpreter_env_controller {
  Interpreter& interpreter;
  Environment* old_environment;
  Interpreter_env_controller(Interpreter&, std::shared_ptr<Environment>);
  ~Interpreter_env_controller();
};

struct Return_hack {
  Neem_value value;
};

#endif // !INTERPRETER_H
