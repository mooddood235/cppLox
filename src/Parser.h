#pragma once
#include <vector>
#include "Token.h"
#include "Expr.h"
#include "Stmt.h"

class Parser{
public:
	Parser(const std::vector<Token>& tokens);
	std::vector<Stmt*> Parse();
private:
	Stmt* VarDecleration();
	Stmt* Decleration();
	Stmt* Statement();
	Stmt* PrintStatement();
	Stmt* IfStatement();
	Stmt* ExpressionStatement();
	Stmt* WhileStatement();
	Stmt* ForStatement();
	Function* ParseFunction(const std::string& kind);
	std::vector<Stmt*> ParseBlock();
	Expr* Expression();
	Expr* Equality();
	Expr* Comparison();
	Expr* Term();
	Expr* Factor();
	Expr* ParseUnary();
	Expr* Primary();
	Expr* Assignment();
	Expr* Or();
	Expr* And();
	Expr* ParseCall();
	Expr* FinishCall(Expr* callee);
	Token Consume(const TokenType type, const std::string& message);
	bool Match(const std::vector<TokenType>& types);
	bool Check(const TokenType type) const;
	Token Advance();
	bool IsAtEnd() const;
	Token Peek() const;
	Token Previous() const;
	class ParseError {};
	ParseError ParserError(const Token& token, const std::string& message);
	void Synchronize();
private:
	std::vector<Token> tokens;
	int current = 0;
private:	
};

