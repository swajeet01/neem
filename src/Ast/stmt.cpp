/*******************************
*	File generated by ast_generator.py, DO NOT MODIFY!
*******************************/

#include <memory>
#include <vector>

#include "expr.hpp"
#include "../Visitor/mutable_state_visitor.hpp"

#include "stmt.hpp"

Block::Block(std::vector<std::shared_ptr<Stmt>> p_statements):
	statements {p_statements} {}

void Block::accept(Mutable_state_visitor& visitor) {
	visitor.visit(*this);
}

Expression::Expression(std::shared_ptr<Expr> p_expression):
	expression {p_expression} {}

void Expression::accept(Mutable_state_visitor& visitor) {
	visitor.visit(*this);
}

If::If(std::shared_ptr<Expr> p_condition, std::shared_ptr<Stmt> p_then_branch, std::shared_ptr<Stmt> p_else_branch):
	condition {p_condition}, then_branch {p_then_branch}, else_branch {p_else_branch} {}

void If::accept(Mutable_state_visitor& visitor) {
	visitor.visit(*this);
}

Print::Print(std::shared_ptr<Expr> p_expression):
	expression {p_expression} {}

void Print::accept(Mutable_state_visitor& visitor) {
	visitor.visit(*this);
}

Var::Var(Token p_name, std::shared_ptr<Expr> p_initializer):
	name {p_name}, initializer {p_initializer} {}

void Var::accept(Mutable_state_visitor& visitor) {
	visitor.visit(*this);
}

While::While(std::shared_ptr<Expr> p_condition, std::shared_ptr<Stmt> p_body):
	condition {p_condition}, body {p_body} {}

void While::accept(Mutable_state_visitor& visitor) {
	visitor.visit(*this);
}

