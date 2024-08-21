#pragma once
#include "TokenType.h"
#include <string>
#include <any>

struct Literal;

struct Token{
public:
	Token();
	Token(TokenType type, const std::string& lexeme, const std::any& literal, const int line);
	Token(TokenType type, const std::string& lexeme, const int line);
	std::string ToString() const;
public:
	TokenType type;
	std::string lexeme;
	std::any literal;
	int line;
};

