#ifndef MUTABLE_STATE_VISITOR_H
#define MUTABLE_STATE_VISITOR_H

#include "../Ast/expr_fwd.h"
#include "../Ast/stmt_fwd.h"

#include <memory>

struct Mutable_state_visitor {
  virtual void visit(Binary&) = 0;
  virtual void visit(Unary&) = 0;
  virtual void visit(Grouping&) = 0;
  virtual void visit(Ast_literal&) = 0;
  virtual void visit(Print&) = 0;
  virtual void visit(Expression&) = 0;
};

#endif // !MUTABLE_STATE_VISITOR_H
