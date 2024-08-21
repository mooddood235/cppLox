#include "Scanner.h"
#include "cppLox.h"
#include "Expr.h"
#include <any>

Scanner::Scanner(const std::string& source){
	this->source = source;
}

std::vector<Token> Scanner::ScanTokens(){
	while (!IsAtEnd()) {
		start = current;
		ScanToken();
	}
	tokens.push_back(Token(_EOF, "\0", line));
	return tokens;
}

void Scanner::ScanToken(){
	char c = Advance();
	switch (c) {
		case '(': AddToken(LEFT_PAREN); break;
		case ')': AddToken(RIGHT_PAREN); break;
		case '{': AddToken(LEFT_BRACE); break;
		case '}': AddToken(RIGHT_BRACE); break;
		case ',': AddToken(COMMA); break;
		case '.': AddToken(DOT); break;
		case '-': AddToken(MINUS); break;
		case '+': AddToken(PLUS); break;
		case ';': AddToken(SEMICOLON); break;
		case '*': AddToken(STAR); break;
		case '!': AddToken(Match('=') ? BANG_EQUAL : BANG); break;
		case '=': AddToken(Match('=') ? EQUAL_EQUAL : EQUAL); break;
		case '<': AddToken(Match('=') ? LESS_EQUAL : LESS); break;
		case '>': AddToken(Match('=') ? GREATER_EQUAL : GREATER); break;
		case '/':
			if (Match('/')) {
				while (Peek() != '\n' && !IsAtEnd()) Advance();
			}
			else AddToken(SLASH);
			break;
		case ' ':
		case '\r':
		case '\t':
			break;
		case '\n': line++; break;
		case '"': ScanString(); break;
		default: 
			if (isdigit(c)) ScanNumber();
			else if (IsAlpha_(c)) ScanIdentifier();
			else Error(line, "Unexpected character."); break;
	}
}

char Scanner::Advance(){
	return source[current++];
}



bool Scanner::Match(char expected){
	if (IsAtEnd()) return false;
	if (source[current] != expected) return false;
	current++;
	return true;
}

char Scanner::Peek(){
	if (IsAtEnd()) return '\0';
	return source[current];
}

char Scanner::PeekNext(){
	if (current + 1 >= source.size()) return '\0';
	return source[current + 1];
}

void Scanner::ScanString(){
	while (Peek() != '"' && !IsAtEnd()) {
		if (Peek() == '\n') line++;
		Advance();
	}
	if (IsAtEnd()) {
		Error(line, "Unterminated string.");
		return;
	}
	Advance();
	AddToken(STRING, source.substr(start + 1, current - start - 2));
}

void Scanner::ScanNumber(){
	while (isdigit(Peek())) Advance();
	if (Peek() == '.' && isdigit(PeekNext())) {
		Advance();
		while (isdigit(Peek())) Advance();
	}
	AddToken(NUMBER, std::stod(source.substr(start, current - start)));
}

void Scanner::ScanIdentifier(){
	while (IsAlpha_Numeric(Peek())) Advance();
	std::string text = source.substr(start, current - start);
	if (keywords.find(text) != keywords.end()) AddToken(keywords[text]);
	else AddToken(IDENTIFIER);
}

bool Scanner::IsAlpha_(const char c){
	return isalpha(c) || c == '_';
}
bool Scanner::IsAlpha_Numeric(const char c) {
	return IsAlpha_(c) || isdigit(c);
}
void Scanner::AddToken(TokenType type) {
	std::string text = source.substr(start, current - start);
	tokens.push_back(Token(type, text, line));
}
void Scanner::AddToken(TokenType type, std::any literal){
	std::string text = source.substr(start, current - start);
	tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::IsAtEnd(){
	return current >= source.size();
}
