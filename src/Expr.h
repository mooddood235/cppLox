#pragma once
#include <string>
#include "Token.h"
#include "ExprVisitor.h"
#include <any>

struct Expr {
public:
	virtual std::any Accept(ExprVisitor<std::any>* visitor) const = 0;
	virtual ~Expr();
};
struct Literal : Expr {
public:
	Literal(const std::string& s);
	Literal(const double d);
	Literal(const bool b);
	Literal();
	std::string ToString() const;
	std::any Accept(ExprVisitor<std::any>* visitor) const override;
	std::any data;
private:
	enum LiteralType {
		STRING,
		NUMBER,
		BOOL,
		NIL
	 };
	LiteralType type;
};
struct Unary : Expr {
public:
	Unary(const Token& op, Expr* right);
	std::any Accept(ExprVisitor<std::any>* visitor) const override;
	Token op;
	Expr* right;
	~Unary();
};
struct Binary : Expr {
public:
	Binary(Expr* left, const Token& op, Expr* right);
	std::any Accept(ExprVisitor<std::any>* visitor) const override;
	Expr* left;
	Token op;
	Expr* right;
	~Binary();
};
struct Grouping : Expr {
public:
	Grouping(Expr* expr);
	std::any Accept(ExprVisitor<std::any>* visitor) const override;
	Expr* expr;
	~Grouping();
};
struct Variable : Expr {
public:
	Variable(const Token& name);
	std::any Accept(ExprVisitor<std::any>* visitor) const override;
	Token name;
};
struct Assign : Expr {
public:
	Assign(const Token& name, Expr* value);
	std::any Accept(ExprVisitor<std::any>* visitor) const override;
	Token name;
	Expr* value;
	~Assign();
};
struct Logical :Expr {
	Logical(Expr* left, Token op, Expr* right);
	std::any Accept(ExprVisitor<std::any>* visitor) const override;
	Expr* left;
	Token op;
	Expr* right;
	~Logical();
};