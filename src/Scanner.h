#pragma once
#include "Token.h"
#include <vector>
#include <unordered_map>
#include <any>

class Scanner{
public:
	Scanner(const std::string& source);
	std::vector<Token> ScanTokens();
private:
	bool IsAtEnd();
	void ScanToken();
	char Advance();
	void AddToken(TokenType type, std::any literal);
	void AddToken(TokenType type);
	bool Match(char expected);
	char Peek();
	char PeekNext();
	void ScanString();
	void ScanNumber();
	void ScanIdentifier();
	bool IsAlpha_(const char c);
	bool IsAlpha_Numeric(const char c);
private:
	std::string source;
	std::vector<Token> tokens;
	int start = 0;
	int current = 0;
	int line = 1;
	std::unordered_map<std::string, TokenType> keywords = {
		{"and", AND},
		{"class", CLASS},
		{"else", ELSE},
		{"false", FALSE},
		{"for", FOR},
		{"fun", FUN},
		{"if", IF},
		{"nil", NIL},
		{"or", OR},
		{"print", PRINT},
		{"return", RETURN},
		{"super", SUPER},
		{"this", THIS},
		{"true", TRUE},
		{"var", VAR},
		{"while", WHILE}
	};
};

