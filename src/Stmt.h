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
	~Var();
	Token name;
	Expr* initializer;
};
struct Block : Stmt {
public:
	Block(const std::vector<Stmt*>& stmts);
	void Accept(StmtVisitor<void>* visitor) const override;
	std::vector<Stmt*> stmts = std::vector<Stmt*>();
	~Block();
};
struct If : Stmt {
public:
	If(Expr* conditional, Stmt* thenBranch, Stmt* elseBranch);
	void Accept(StmtVisitor<void>* visitor) const override;
	Expr* conditional;
	Stmt* thenBranch;
	Stmt* elseBranch;
	~If();

};
struct While : Stmt {
public:
	While(Expr* condition, Stmt* body);
	void Accept(StmtVisitor<void>* visitor) const override;
	Expr* condition;
	Stmt* body;
	~While();
};
struct Function : Stmt {
	Function();
	Function(const Token& name, const std::vector<Token> params,
		const std::vector<Stmt*> body);
	void Accept(StmtVisitor<void>* visitor) const override;
	Token name;
	std::vector<Token> params;
	std::vector<Stmt*> body;
	~Function();
};