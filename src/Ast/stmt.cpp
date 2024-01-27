/*******************************
*	File generated by ast_generator.py, DO NOT MODIFY!
*******************************/

#include <memory>
#include <vector>

#include "expr.hpp"
#include "Visitor/mutable_state_visitor.hpp"
#include "Token/token.hpp"

#include "Ast/stmt.hpp"

Block::Block(std::vector<std::shared_ptr<Stmt>> p_statements):
	statements {std::move(p_statements)} {}

void Block::accept(Mutable_state_visitor& visitor) {
	visitor.visit(this);
}

Expression::Expression(std::shared_ptr<Expr> p_expression):
	expression {std::move(p_expression)} {}

void Expression::accept(Mutable_state_visitor& visitor) {
	visitor.visit(this);
}

Function::Function(Token p_name, std::vector<Token> p_params, std::vector<std::shared_ptr<Stmt>> p_body):
	name {std::move(p_name)}, params {std::move(p_params)}, body {std::move(p_body)} {}

void Function::accept(Mutable_state_visitor& visitor) {
	visitor.visit(this);
}

Return::Return(Token p_keyword, std::shared_ptr<Expr> p_value):
	keyword {std::move(p_keyword)}, value {std::move(p_value)} {}

void Return::accept(Mutable_state_visitor& visitor) {
	visitor.visit(this);
}

If::If(std::shared_ptr<Expr> p_condition, std::shared_ptr<Stmt> p_then_branch, std::shared_ptr<Stmt> p_else_branch):
	condition {std::move(p_condition)}, then_branch {std::move(p_then_branch)}, else_branch {std::move(p_else_branch)} {}

void If::accept(Mutable_state_visitor& visitor) {
	visitor.visit(this);
}

Print::Print(std::shared_ptr<Expr> p_expression):
	expression {std::move(p_expression)} {}

void Print::accept(Mutable_state_visitor& visitor) {
	visitor.visit(this);
}

Var::Var(Token p_name, std::shared_ptr<Expr> p_initializer):
	name {std::move(p_name)}, initializer {std::move(p_initializer)} {}

void Var::accept(Mutable_state_visitor& visitor) {
	visitor.visit(this);
}

While::While(std::shared_ptr<Expr> p_condition, std::shared_ptr<Stmt> p_body):
	condition {std::move(p_condition)}, body {std::move(p_body)} {}

void While::accept(Mutable_state_visitor& visitor) {
	visitor.visit(this);
}

