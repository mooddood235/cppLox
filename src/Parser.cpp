#include "Parser.h"
#include "TokenType.h"
#include "cppLox.h"
#include <format>

Parser::Parser(const std::vector<Token>& tokens) {
	this->tokens = tokens;
}
std::vector<Stmt*> Parser::Parse(){
	std::vector<Stmt*> statements = std::vector<Stmt*>();
	while (!IsAtEnd()) {
		statements.push_back(Decleration());
	}
	return statements;
}
Stmt* Parser::VarDecleration(){
	Token name = Consume(IDENTIFIER, "Expect variable name.");

	Expr* initializer = nullptr;
	if (Match({ EQUAL })) initializer = Expression();

	Consume(SEMICOLON, "Expect ';' after variable decleration.");
	return new Var(name, initializer);
}
Stmt* Parser::ClassDecleration(){
	Token name = Consume(IDENTIFIER, "Expect class name.");
	Consume(LEFT_BRACE, "Expect '{' before class body.");
	
	std::vector<Function*> methods = std::vector<Function*>();
	while (!Check(RIGHT_BRACE) && !IsAtEnd())
		methods.push_back(ParseFunction("method"));
	
	Consume(RIGHT_BRACE, "Expect '}' after class body.");
	return new Class(name, methods);
}
Stmt* Parser::Decleration(){
	try {
		if (Match({ CLASS })) return ClassDecleration();
		if (Match({ FUN })) return ParseFunction("function");
		if (Match({ VAR })) return VarDecleration();
		if (Match({ LEFT_BRACE })) return new Block(ParseBlock());
		return Statement();
	}
	catch (ParseError error) {
		Synchronize();
		return nullptr;
	}
}
Stmt* Parser::Statement(){
	if (Match({ IF })) return IfStatement();
	if (Match({ PRINT })) return PrintStatement();
	if (Match({ RETURN })) return ReturnStatement();
	if (Match({ WHILE })) return WhileStatement();
	if (Match({ FOR })) return ForStatement();
	if (Match({ LEFT_BRACE })) return new Block(ParseBlock());
	return ExpressionStatement();
}
Stmt* Parser::PrintStatement(){
	Expr* expr = Expression();
	Consume(SEMICOLON, "Expect ';' after value.");
	return new Print(expr);
}
Stmt* Parser::IfStatement(){
	Consume(LEFT_PAREN, "Expect '(' after 'if'.");
	Expr* condition = Expression();
	Consume(RIGHT_PAREN, "Expect ')' after if condition.");

	Stmt* thenBranch = Statement();
	Stmt* elseBranch = nullptr;

	if (Match({ ELSE })) elseBranch = Statement();

	return new If(condition, thenBranch, elseBranch);
}
Stmt* Parser::ExpressionStatement(){
	Expr* expr = Expression();
	Consume(SEMICOLON, "Expect ';' after expression.");
	return new ExprStmt(expr);
}
Stmt* Parser::WhileStatement(){
	Consume(LEFT_PAREN, "Expect '(' after 'while'.");
	Expr* condition = Expression();
	Consume(RIGHT_PAREN, "Expect '(' after condition.");

	Stmt* body = Statement();

	return new While(condition, body);

}
Stmt* Parser::ForStatement(){
	Consume(LEFT_PAREN, "Expect '(' after 'for'.");

	Stmt* initializer;
	if (Match({ SEMICOLON })) initializer = nullptr;
	else if (Match({ VAR })) initializer = VarDecleration();
	else initializer = ExpressionStatement();

	Expr* condition = nullptr;
	if (!Check(SEMICOLON)) condition = Expression();
	Consume(SEMICOLON, "Expect ';' after loop condition.");

	Expr* increment = nullptr;
	if (!Check(RIGHT_PAREN)) increment = Expression();
	Consume(RIGHT_PAREN, "Expect ')' after for clauses.");

	Stmt* body = Statement();
	
	if (increment) body = new Block({ body, new ExprStmt(increment) });
	if (!condition) condition = new Literal(true);
	
	body = new While(condition, body);

	if (initializer) body = new Block({ initializer, body });

	return body;
}
Stmt* Parser::ReturnStatement(){
	Token keyword = Previous();
	Expr* value = nullptr;
	if (!Check(SEMICOLON)) value = Expression();
	Consume(SEMICOLON, "Excpect ';' after return value.");
	return new Return(keyword, value);
}
Function* Parser::ParseFunction(const std::string& kind){
	Token name = Consume(IDENTIFIER, std::format("Expect {} name.", kind));
	Consume(LEFT_PAREN, std::format("Expect '(' after {} name.", kind));
	std::vector<Token> parameters = std::vector<Token>();
	if (!Check(RIGHT_PAREN)) {
		do {
			if (parameters.size() >= 255) {
				Error(Peek(), "Can't have more than 255 parameters.");
			}
			parameters.push_back(Consume(IDENTIFIER, "Expect parameter name."));
		} while (Match({ COMMA }));
	}
	Consume(RIGHT_PAREN, "Expect ')' after parameters.");
	Consume(LEFT_BRACE, "Expect '{' before " + kind + " body.");
	std::vector<Stmt*> body = ParseBlock();
	return new Function(name, parameters, body);
}
std::vector<Stmt*> Parser::ParseBlock(){
	std::vector<Stmt*> stmts = std::vector<Stmt*>();

	while (!Check({ RIGHT_BRACE }) && !IsAtEnd()) {
		stmts.push_back(Decleration());
	}
	Consume(RIGHT_BRACE, "Expect '}' after block.");
	return stmts;
}
Expr* Parser::Expression(){
	return Assignment();
}
Expr* Parser::Equality(){
	Expr* expr = Comparison();
	while (Match({BANG_EQUAL, EQUAL_EQUAL})) {
		Token op = Previous();
		Expr* right = Comparison();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::Comparison(){
	Expr* expr = Term();
	while (Match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL})) {
		Token op = Previous();
		Expr* right = Term();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::Term(){
	Expr* expr = Factor();

	while (Match({MINUS, PLUS})) {
		Token op = Previous();
		Expr* right = Factor();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::Factor(){
	Expr* expr = ParseUnary();

	while (Match({SLASH, STAR})) {
		Token op = Previous();
		Expr* right = ParseUnary();
		expr = new Binary(expr, op, right);
	}
	return expr;
}

Expr* Parser::ParseUnary(){
	if (Match({BANG, MINUS})) {
		Token op = Previous();
		Expr* right = ParseUnary();
		return new Unary(op, right);
	}
	return ParseCall();
}

Expr* Parser::Primary(){
	if (Match({ FALSE })) return new Literal(false);
	if (Match({ TRUE })) return new Literal(true);
	if (Match({ NIL })) return new Literal();

	if (Match({ NUMBER })) {
		const double n = std::any_cast<double>(Previous().literal);
		return new Literal(n);
	}
	if (Match({ STRING })) {
		const std::string s = std::any_cast<std::string>(Previous().literal);
		return new Literal(s);
	}
	if (Match({ IDENTIFIER })) {
		return new Variable(Previous());
	}
	if (Match({ LEFT_PAREN })) {
		Expr* expr = Expression();
		Consume(RIGHT_PAREN, "Expect ')' after expression.");
		return new Grouping(expr);
	}
	throw ParserError(Peek(), "Expect expression.");
}

Expr* Parser::Assignment(){
	Expr* expr = Or();

	if (Match({ EQUAL })) {
		Token equals = Previous();
		Expr* value = Assignment();

		Variable* variable = dynamic_cast<Variable*>(expr);
		if (variable) return new Assign(variable->name, value);
		
		Error(equals, "Invalid assignment target.");
	}
	return expr;
}

Expr* Parser::Or(){
	Expr* expr = And();

	while (Match({ OR })) {
		Token op = Previous();
		Expr* right = And();
		expr = new Logical(expr, op, right);
	}
	return expr;
}

Expr* Parser::And(){
	Expr* expr = Equality();

	while (Match({ AND })) {
		Token op = Previous();
		Expr* right = Equality();
		expr = new Logical(expr, op, right);
	}
	return expr;
}

Expr* Parser::ParseCall(){
	Expr* expr = Primary();

	while (true) {
		if (Match({ LEFT_PAREN })) expr = FinishCall(expr);
		else break;
	}
	return expr;
}

Expr* Parser::FinishCall(Expr* callee){
	std::vector<Expr*> arguments = std::vector<Expr*>();

	if (!Check(RIGHT_PAREN)) {
		do {
			if (arguments.size() >= 255) Error(Peek(), "Can't have more than 255 arguments.");
			arguments.push_back(Expression());
		} while (Match({ COMMA }));
	}
	Token paren = Consume(RIGHT_PAREN, "Expect ')' after arguments.");
	return new Call(callee, paren, arguments);
}

Token Parser::Consume(const TokenType type, const std::string& message){
	if (Check(type)) return Advance();
	throw ParserError(Peek(), message);
}
bool Parser::Match(const std::vector<TokenType>& types){
	for (const TokenType type : types) {
		if (Check(type)) {
			Advance();
			return true;
		}
	}
	return false;
}

bool Parser::Check(const TokenType type) const{
	if (IsAtEnd()) return false;
	return Peek().type == type;
}

Token Parser::Advance(){
	if (!IsAtEnd()) current++;
	return Previous();
}

bool Parser::IsAtEnd() const{
	return Peek().type == _EOF;
}

Token Parser::Peek() const{
	return tokens[current];
}

Token Parser::Previous() const{
	return tokens[current - 1];
}

Parser::ParseError Parser::ParserError(const Token& token, const std::string& message){
	Error(token, message);
	return ParseError();
}

void Parser::Synchronize(){
	Advance();
	while (!IsAtEnd()) {
		if (Previous().type == SEMICOLON) return;

		switch (Peek().type) {
			case CLASS: case FOR: case FUN: case IF: case PRINT:
			case RETURN: case VAR: case WHILE:
				return;
		}
		Advance();
	}
}


