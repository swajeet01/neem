#ifndef MUTABLE_STATE_VISITOR_H
#define MUTABLE_STATE_VISITOR_H

#include "../Ast/expr_fwd.hpp"
#include "../Ast/stmt_fwd.hpp"

#include <memory>

struct Mutable_state_visitor {
  virtual void visit(Binary&) = 0;
  virtual void visit(Unary&) = 0;
  virtual void visit(Grouping&) = 0;
  virtual void visit(Ast_literal&) = 0;
  virtual void visit(Print&) = 0;
  virtual void visit(Expression&) = 0;
  virtual void visit(Var&) = 0;
  virtual void visit(Variable&) = 0;
  virtual void visit(Assign&) = 0;
  virtual void visit(Block&) = 0;
  virtual void visit(If&) = 0;
  virtual void visit(Logical&) = 0;
  virtual void visit(While&) = 0;
};

#endif // !MUTABLE_STATE_VISITOR_H
