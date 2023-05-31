/*******************************
*	File generated by ast_generator.py, DO NOT MODIFY!
*******************************/

#ifndef STMT_H
#define STMT_H

#include <memory>
#include <vector>

#include "expr.h"
#include "../Visitor/mutable_state_visitor.h"

struct Stmt {
	virtual void accept(Mutable_state_visitor&) = 0;
};

struct Block: public Stmt {
	std::vector<std::shared_ptr<Stmt>> statements;
	Block(std::vector<std::shared_ptr<Stmt>>);
	void accept(Mutable_state_visitor&);
};

struct Expression: public Stmt {
	std::shared_ptr<Expr> expression;
	Expression(std::shared_ptr<Expr>);
	void accept(Mutable_state_visitor&);
};

struct Print: public Stmt {
	std::shared_ptr<Expr> expression;
	Print(std::shared_ptr<Expr>);
	void accept(Mutable_state_visitor&);
};

struct Var: public Stmt {
	Token name;
	std::shared_ptr<Expr> initializer;
	Var(Token, std::shared_ptr<Expr>);
	void accept(Mutable_state_visitor&);
};


#endif
