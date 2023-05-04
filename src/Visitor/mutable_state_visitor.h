#ifndef MUTABLE_STATE_VISITOR_H
#define MUTABLE_STATE_VISITOR_H

#include "../Ast/expr_fwd.h"

#include <memory>

struct Mutable_state_visitor {
  void visit(Binary&) = 0;
  void visit(Unary&) = 0;
  void visit(Grouping&) = 0;
  void visit(Ast_literal&) = 0;
};

#endif // !MUTABLE_STATE_VISITOR_H
