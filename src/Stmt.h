#pragma once
#include "Expr.h"
#include "StmtVisitor.h"

struct Stmt{
public:
	virtual void Accept(StmtVisitor<void>* visitor) const = 0;
	virtual ~Stmt();
};
struct ExprStmt : Stmt{
public:
	void Accept(StmtVisitor<void>* visitor) const override;
	ExprStmt(Expr* expr);
	~ExprStmt();
	Expr* expr;
};
struct Print : Stmt {
public:
	void Accept(StmtVisitor<void>* visitor) const override;
	Print(Expr* expr);
	~Print();
	Expr* expr;
};
struct Var : Stmt {
public:
	void Accept(StmtVisitor<void>* visitor) const override;
	Var(const Token& name, Expr* initializer);
	Token name;
	Expr* initializer;
};
struct Block : Stmt {
public:
	Block(const std::vector<Stmt*>& stmts);
	void Accept(StmtVisitor<void>* visitor) const override;
	std::vector<Stmt*> stmts = std::vector<Stmt*>();
};
struct If : Stmt {
public:
	If(Expr* conditional, Stmt* thenBranch, Stmt* elseBranch);
	void Accept(StmtVisitor<void>* visitor) const override;
	Expr* conditional;
	Stmt* thenBranch;
	Stmt* elseBranch;

};