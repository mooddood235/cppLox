#include "Token.h"
#include "Expr.h"

Token::Token(){
	type = TokenType::NIL;
	line = 0;
}
Token::Token(TokenType type, const std::string& lexeme, const std::any& literal, const int line){
	this->type = type;
	this->lexeme = lexeme;
	this->literal = literal;
	this->line = line;
}

Token::Token(TokenType type, const std::string& lexeme, const int line){
	this->type = type;
	this->lexeme = lexeme;
	this->literal = NULL;
	this->line = line;
}

std::string Token::ToString() const{
	std::string stringLiteral = "";
	if (type == STRING) stringLiteral = std::any_cast<std::string>(literal);
	else if (type == NUMBER) stringLiteral = std::to_string(std::any_cast<double>(literal));
	return tokenTypeToString[type] + " " + lexeme + " " + stringLiteral;
}
