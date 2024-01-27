#ifndef RESOLVER_HPP
#define RESOLVER_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Token/token.hpp"
#include "Visitor/interpreter.hpp"
#include "Visitor/mutable_state_visitor.hpp"
#include "Ast/stmt_fwd.hpp"

enum class Function_type { NONE, FUNCTION };

class Resolver: public Mutable_state_visitor {
public:
  using Map = std::unordered_map<std::string, bool>;
  explicit Resolver(Interpreter&);
  void resolve(std::vector<std::shared_ptr<Stmt>>&);
private:
  Interpreter& interpreter;
  // I am too lazy to right write a Resolver_error_reporter right now,
  // I may write one later but till then I'll just use
  // Interpreter's error reporter.
  std::vector<Map> scopes;
  Function_type current_function {Function_type::NONE};
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
  void begin_scope();
  void end_scope();
  void declare(Token&);
  void define(Token&);
  void resolve(std::shared_ptr<Stmt>&);
  void resolve(std::shared_ptr<Expr>&);
  void resolve_local(Expr*, Token&);
  void resolve_function(Function*, Function_type);
};

#endif // !RESOLVER_HPP
